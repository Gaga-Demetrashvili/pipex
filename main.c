/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:03:38 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/22 23:24:08 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child_process_logic(t_model *model)
{
	int	infile_fd;
	int	res;

	res = 0;
	infile_fd = open_file(model->infile_name, 1);
	if (infile_fd < 0)
		return (1);
	close(model->read_end_of_pipe);
	if (dup2(infile_fd, STDIN_FILENO) < 0)
	{
		perror("dup2 failed for infile");
		res = 1;
	}
	close(infile_fd);
	if (dup2(model->write_end_of_pipe, STDOUT_FILENO) < 0)
	{
		perror("dup2 failed for pipe write end");
		res = 1;
	}
	close(model->write_end_of_pipe);
	return (res);
}

void	print_arr(char **str_arr)
{
	int	i;

	if (!str_arr)
		return ;
	i = 0;
	while (str_arr[i])
	{
		ft_printf("%s\n", str_arr[i]);
		i++;
	}
}

int	parent_process_logic(int pid, t_model *model)
{
	int	status;
	int	outfile_fd;
	int	res;

	status = 0;
	res = 0;
	outfile_fd = open_file(model->outfile_name, 0);
	if (outfile_fd < 0)
		return (1);
	waitpid(pid, &status, 0);
	close(model->write_end_of_pipe);
	if (dup2(model->read_end_of_pipe, STDIN_FILENO) < 0)
	{
		perror("dup2 failed for pipe read end");
		res = 1;
	}
	if (dup2(outfile_fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 failed for outfile");
		res = 1;
	}
	close(outfile_fd);
	close(model->read_end_of_pipe);
	return (res);
}

char	*find_path(char **cmdv, char **paths)
{
	int		i;
	char	path;
	char	c;

	i = 0;
	while (paths[i])
	{
		c = ft_strjoin(paths[i], '/');
		path = ft_strjoin(c, cmdv[0]);
		free(c);
		if (0 == access(path, X_OK))
			return (paths[i]);
		i++;
	}
	return (NULL);
}

int	execute_cmd(char *cmd, char **envp)
{
	char	**paths;
	char	**cmdv;
	int		i;
	char	*path;

	cmdv = ft_split(cmd, ' ');
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			paths = ft_split(envp[i] + 5, ':');
		i++;
	}
	path = find_path(cmdv, envp);
	if (!path)
		return (1);
	// print_arr(paths);
	if (execve(path, cmdv, envp) == -1)
	{
		perror("execv failed");
		free_arr(cmdv);
		return (1);
	}
	return (0);
}

int	process_mediator(int pid, t_model *model)
{
	if (pid == 0)
	{
		if (child_process_logic(model))
			return (1);
		execute_cmd(model->cmd1, model->envp);
	}
	else
	{
		if (parent_process_logic(pid, model))
			return (1);
		execute_cmd(model->cmd2, model->envp);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid;
	int		val_res;
	t_model	*model;

	val_res = validations(argc, pipe(pipefd));
	model = create_and_init_model(argv, pipefd, envp);
	if (!model)
		return (1);
	if (val_res)
		return (1);
	pid = fork();
	if (pid < 0)
	{
		perror("Error\nFork failed");
		return (1);
	}
	if (process_mediator(pid, model))
		return (1);
	return (0);
}
