/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:39:44 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/29 21:37:27 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include "../pipex.h"

void	read_write_logic(int i, t_model model, int pipe_wr_end_fd, int prev_fd,
		int is_heredoc)
{
	int	outfile_fd;
	int	infile_fd;

	if (i == 0)
	{
		infile_fd = open_file(model.infile_name, model, 1);
		dup2(infile_fd, STDIN_FILENO);
		close(infile_fd);
		if (is_heredoc)
			unlink(model.infile_name);
	}
	else
		dup2(prev_fd, STDIN_FILENO);
	if (i == model.cmd_c - 1)
	{
		outfile_fd = open_file(model.outfile_name, model, 0);
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
	}
	else
		dup2(pipe_wr_end_fd, STDOUT_FILENO);
}

void	child_proccess_logic(int i, t_model model, int *pipefd, int prev_fd,
		int is_heredoc)
{
	read_write_logic(i, model, pipefd[1], prev_fd, is_heredoc);
	if (prev_fd != -1)
		close(prev_fd);
	close(pipefd[0]);
	close(pipefd[1]);
	execute_cmd(model.cmdv_arr[i], model.envp, model);
}

void	loop_logic(t_model model, int *last_pid, int is_heredoc)
{
	int		i;
	int		prev_fd;
	int		pipefd[2];
	pid_t	pid;

	i = 0;
	prev_fd = -1;
	while (i < model.cmd_c)
	{
		if (i < model.cmd_c - 1)
			pipe(pipefd);
		pid = fork();
		if (pid == 0)
			child_proccess_logic(i, model, pipefd, prev_fd, is_heredoc);
		if (i == model.cmd_c - 1)
			*last_pid = pid;
		if (prev_fd != -1)
			close(prev_fd);
		if (i < model.cmd_c - 1)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		i++;
	}
}

int	main_logic(t_model model, int is_heredoc)
{
	pid_t	last_pid;
	int		status;
	int		last_exit;
	pid_t	wpid;

	last_pid = 0;
	loop_logic(model, &last_pid, is_heredoc);
	wpid = wait(&status);
	while (wpid > 0)
	{
		if (wpid == last_pid)
		{
			if (WIFEXITED(status))
				last_exit = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_exit = 128 + WTERMSIG(status);
		}
		wpid = wait(&status);
	}
	return (last_exit);
}

void	heredoc_logic(char *limiter, char *heredoc_infile_name)
{
	int		stdin_fd;
	char	*line;
	char	*limiter_with_n;
	char	tmp_file_fd;

	stdin_fd = 0;
	tmp_file_fd = open(heredoc_infile_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	limiter_with_n = ft_strjoin(limiter, "\n");
	ft_printf("> ");
	line = get_next_line(stdin_fd);
	while (line && ft_strcmp(line, limiter_with_n))
	{
		write(tmp_file_fd, line, ft_strlen(line));
		free(line);
		ft_printf("> ");
		line = get_next_line(stdin_fd);
	}
	close(tmp_file_fd);
	free(limiter_with_n);
	if (line)
		free(line);
}

int	main(int argc, char **argv, char **envp)
{
	t_model	model;
	int		status;
	char	*here_doc_infile_name;
	int		is_heredoc;

	validations_b(argc, argv);
	here_doc_infile_name = NULL;
	is_heredoc = 0;
	if (!ft_strcmp(argv[1], "here_doc"))
	{
		here_doc_infile_name = "heredoc_tmp.txt";
		is_heredoc = 1;
		heredoc_logic(argv[2], here_doc_infile_name);
	}
	model = create_and_init_model(argv, argc, envp, is_heredoc,
			here_doc_infile_name);
	status = main_logic(model, is_heredoc);
	clean_up_resources(model);
	return (status);
}
