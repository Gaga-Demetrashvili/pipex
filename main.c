/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:03:38 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/18 22:42:25 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//#include <signal.h>

int	open_file(char *file_name, int is_rdonly)
{
	int		fd;
	char	*file_type;

	file_type = NULL;
	if (is_rdonly)
		fd = open(file_name, O_RDONLY);
	else
		fd = open(file_name, O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		if (is_rdonly)
			file_type = "infile";
		else
			file_type = "outfile";
		ft_printf("Error\nCan't open %s: %s", file_type, strerror(errno));
	}
	return (fd);
}

void	child_process_err_handling(int status)
{
	int	sig;

	ft_printf("Error\n");
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		ft_printf("Child was killed by signal %d (%s)\n", sig, strsignal(sig));
	}
	else if (WIFSTOPPED(status))
	{
		sig = WSTOPSIG(status);
		ft_printf("Child was stopped by signal %d (%s)\n", sig, strsignal(sig));
	}
	else if (WIFCONTINUED(status))
		ft_printf("Child continued\n");
}

// outfile_fd = open_file(argv[4], 0);
// if (outfile_fd < 0)
// 	return (1);

int	child_process_logic(int read_end_of_pipe, int write_end_of_pipe,
		char *infile_name)
{
	int	infile_fd;

	infile_fd = open_file(infile_name, 1);
	if (infile_fd < 0)
		return (1);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	dup2(write_end_of_pipe, STDOUT_FILENO);
	close(read_end_of_pipe);
	close(write_end_of_pipe);
	return (0);
}

int	create_pipe(int pid, char *infile_name, char *outfile_name)
{
	int	pipefd[2];
	int	status;

	status = 0;
	if (pipe(pipefd) == -1)
	{
		perror("Error\nPipe error");
		return (1);
	}
	if (pid == 0)
		if (child_process_logic(pipefd[0], pipefd[1], infile_name))
			return (1);
		else
		{
			waitpid(pid, &status, 0);
			if (!WIFEXITED(status))
			{
				child_process_err_handling(status);
				return (1);
			}
			ft_printf("Parent process id: %d, Child process id: %d\n", getpid(),
				pid);
		}
	return (0);
}

int	fork_process(char *infile_name, char *outfile_name)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Error\nFork failed");
		return (1);
	}
	if (create_pipe(pid))
		return (1);
	// if (pid == 0)
	// 	kill(getpid(), SIGKILL);
	// if (pid == 0)
	// 	ft_printf("Child should execute this\n");
	return (0);
}

// int	main(int argc, char **argv, char **envp)
int	main(int argc, char **argv)
{
	int	outfile_fd;

	if (argc != 5)
	{
		ft_printf("Error\nProgram should take 4 args");
		return (1);
	}
	if (fork_process(argv[1], argv[4]))
		return (1);
	return (0);
}
