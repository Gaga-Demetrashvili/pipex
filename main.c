/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:03:38 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/24 12:59:59 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_cmd(char **cmdv, char **envp, t_model *model)
{
	int		i;
	char	*path;

	i = 0;
	path = find_path(cmdv, envp);
	if (!path)
		ft_error_exit(cmdv[0], ": command not found\n", model, 1);
	if (execve(path, cmdv, envp) == -1)
	{
		perror("execv failed");
		free(path);
		clean_up_resources(model);
		exit(1);
	}
}

void	child_process_logic(t_model *model)
{
	int	infile_fd;

	infile_fd = open_file(model->infile_name, model, 1);
	close(model->read_end_of_pipe);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	dup2(model->write_end_of_pipe, STDOUT_FILENO);
	close(model->write_end_of_pipe);
	execute_cmd(model->cmdv1, model->envp, model);
}

void	parent_process_logic(int pid, t_model *model)
{
	int	status;
	int	outfile_fd;

	status = 0;
	outfile_fd = open_file(model->outfile_name, model, 0);
	waitpid(pid, &status, 0);
	close(model->write_end_of_pipe);
	dup2(model->read_end_of_pipe, STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	close(model->read_end_of_pipe);
	execute_cmd(model->cmdv2, model->envp, model);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid;
	t_model	*model;

	validations(argc, argv, pipe(pipefd));
	model = create_and_init_model(argv, pipefd, envp);
	if (!model)
		return (1);
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		clean_up_resources(model);
		return (1);
	}
	if (pid == 0)
		child_process_logic(model);
	else
		parent_process_logic(pid, model);
	clean_up_resources(model);
	return (0);
}
