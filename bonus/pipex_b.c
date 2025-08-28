/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:39:44 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/28 23:25:55 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include "../pipex.h"

void	read_write_logic(int i, t_model model, int pipe_wr_end_fd, int prev_fd)
{
	int	outfile_fd;
	int	infile_fd;

	if (i == 0)
	{
		infile_fd = open_file(model.infile_name, model, 1);
		dup2(infile_fd, STDIN_FILENO);
		close(infile_fd);
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

void	child_proccess_logic(int i, t_model model, int *pipefd, int prev_fd)
{
	read_write_logic(i, model, pipefd[1], prev_fd);
	if (prev_fd != -1)
		close(prev_fd);
	close(pipefd[0]);
	close(pipefd[1]);
	execute_cmd(model.cmdv_arr[i], model.envp, model);
}

void	loop_logic(t_model model, int *last_pid)
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
			child_proccess_logic(i, model, pipefd, prev_fd);
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

int	main_logic(t_model model)
{
	pid_t	last_pid;
	int		status;
	int		last_exit;
	pid_t	wpid;

	last_pid = 0;
	loop_logic(model, &last_pid);
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

void	heredoc_logic(char *limiter)
{
	int		fd;
	char	*line;
	char	*limiter_with_n;

	fd = 1;
	limiter_with_n = ft_strjoin(limiter, "\n");
	ft_printf("> ");
	line = get_next_line(fd);
	while (line && ft_strcmp(line, limiter_with_n))
	{
		free(line);
		ft_printf("> ");
		line = get_next_line(fd);
	}
	free(limiter_with_n);
}

int	main(int argc, char **argv, char **envp)
{
	t_model	model;
	int		status;

	validations_b(argc, argv);
	if (!ft_strcmp(argv[1], "here_doc"))
	{
		ft_printf("heredoc_logic start!\n");
		heredoc_logic(argv[2]);
		ft_printf("heredoc_logic end!\n");
		exit(0);
	}
	model = create_and_init_model(argv, argc, envp);
	status = main_logic(model);
	clean_up_resources(model);
	return (status);
}
