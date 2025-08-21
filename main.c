/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:03:38 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/21 23:14:16 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child_process_logic(int read_end_of_pipe, int write_end_of_pipe,
		char *infile_name)
{
	int	infile_fd;
	int	res;

	res = 0;
	infile_fd = open_file(infile_name, 1);
	if (infile_fd < 0)
		return (1);
	close(read_end_of_pipe);
	if (dup2(infile_fd, STDIN_FILENO) < 0)
	{
		perror("dup2 failed for infile");
		res = 1;
	}
	close(infile_fd);
	if (dup2(write_end_of_pipe, STDOUT_FILENO) < 0)
	{
		perror("dup2 failed for pipe write end");
		res = 1;
	}
	close(write_end_of_pipe);
	return (res);
}

int	parent_process_logic(int pid, int read_end_of_pipe, int write_end_of_pipe,
		char *outfile_name)
{
	int	status;
	int	outfile_fd;

	status = 0;
	outfile_fd = open_file(outfile_name, 0);
	if (outfile_fd < 0)
		return (1);
	waitpid(pid, &status, 0);
	close(write_end_of_pipe);
	if (dup2(read_end_of_pipe, STDIN_FILENO) < 0)
	{
		perror("dup2 failed for pipe read end");
		exit(1);
	}
	if (dup2(outfile_fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 failed for outfile");
		exit(1);
	}
	close(outfile_fd);
	close(read_end_of_pipe);
	return (0);
}

char	*find_path(char *cmd, char *path)
{
	char	*c;
	char	*tmp;
	char	**paths;
	int		i;
	int		fd;

	i = 0;
	paths = ft_split(path + 5, ':');
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		c = ft_strjoin(tmp, cmd);
		free(tmp);
		fd = open(c, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			return (c);
		}
		free(c);
		i++;
	}
	return (NULL);
}

int	execute_cmd(char *cmd, char **envp)
{
	const char	*cmd_path;
	char		**cmdv;
	int			i;

	cmdv = ft_split(cmd, ' ');
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			break ;
		i++;
	}
	cmd_path = find_path(cmdv[0], envp[i]);
	if (execve(cmd_path, cmdv, envp) == -1)
	{
		perror("execv failed");
		return (1);
	}
	return (0);
}

int	process_mediator(int pid, int *pipefd, char **argv, char **envp)
{
	if (pid == 0)
	{
		if (child_process_logic(pipefd[0], pipefd[1], argv[1]))
			return (1);
		execute_cmd(argv[2], envp);
	}
	else
	{
		if (parent_process_logic(pid, pipefd[0], pipefd[1], argv[4]))
			return (1);
		execute_cmd(argv[3], envp);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid;
	int		val_res;

	val_res = validations(argc, pipe(pipefd));
	if (val_res)
		return (1);
	pid = fork();
	if (pid < 0)
	{
		perror("Error\nFork failed");
		return (1);
	}
	if (process_mediator(pid, pipefd, argv, envp))
		return (1);
	return (0);
}
