/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:03:38 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/29 22:16:07 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	child_process_logic(t_model model, int *pipefd)
{
	int	infile_fd;

	infile_fd = open_file(model.infile_name, model, 1);
	close(pipefd[0]);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	execute_cmd(model.cmdv_arr[0], model.envp, model);
}

int	parent_process_logic(int pid, t_model model, int *pipefd)
{
	int	child2_pid;
	int	status;
	int	outfile_fd;

	status = 0;
	child2_pid = fork();
	if (child2_pid == 0)
	{
		outfile_fd = open_file(model.outfile_name, model, 0);
		waitpid(pid, &status, 0);
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
		close(pipefd[0]);
		execute_cmd(model.cmdv_arr[1], model.envp, model);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(child2_pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

static void	init_pr_args(int argc, char **argv, char **envp, t_pr_args *pr_args)
{
	pr_args->argc = argc;
	pr_args->argv = argv;
	pr_args->envp = envp;
}

int	main(int argc, char **argv, char **envp)
{
	int			pipefd[2];
	pid_t		pid;
	t_model		model;
	int			status;
	t_pr_args	pr_args;

	validations(argc, argv, pipe(pipefd));
	init_pr_args(argc, argv, envp, &pr_args);
	model = create_and_init_model(pr_args, 0, NULL);
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		clean_up_resources(model);
		return (1);
	}
	status = 0;
	if (pid == 0)
		child_process_logic(model, pipefd);
	else
		status = parent_process_logic(pid, model, pipefd);
	clean_up_resources(model);
	return (status);
}
