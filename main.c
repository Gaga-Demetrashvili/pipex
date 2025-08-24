/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:03:38 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/24 12:30:31 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	print_arr(char **str_arr)
// {
// 	int	i;

// 	if (!str_arr)
// 		return ;
// 	i = 0;
// 	while (str_arr[i])
// 	{
// 		ft_printf("%s\n", str_arr[i]);
// 		i++;
// 	}
// }

int	child_process_logic(t_model *model)
{
	int	infile_fd;
	int	res;

	res = 0;
	infile_fd = open_file(model->infile_name, model, 1);
	close(model->read_end_of_pipe);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	dup2(model->write_end_of_pipe, STDOUT_FILENO);
	close(model->write_end_of_pipe);
	return (res);
}

int	parent_process_logic(int pid, t_model *model)
{
	int	status;
	int	outfile_fd;
	int	res;

	status = 0;
	res = 0;
	outfile_fd = open_file(model->outfile_name, model, 0);
	waitpid(pid, &status, 0);
	close(model->write_end_of_pipe);
	dup2(model->read_end_of_pipe, STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	close(model->read_end_of_pipe);
	return (res);
}

int	execute_cmd(char **cmdv, char **envp, t_model *model)
{
	int		i;
	char	*path;
	int		res;

	res = 0;
	i = 0;
	path = find_path(cmdv, envp);
	if (!path)
		ft_error_exit(cmdv[0], ": command not found\n", model, 1);
	if (execve(path, cmdv, envp) == -1)
	{
		perror("execv failed");
		free(path);
		clean_up_resources(model);
		res = 1;
	}
	return (res);
}

int	process_mediator(int pid, t_model *model)
{
	if (pid == 0)
	{
		if (child_process_logic(model))
			return (1);
		execute_cmd(model->cmdv1, model->envp, model);
	}
	else
	{
		if (parent_process_logic(pid, model))
			return (1);
		execute_cmd(model->cmdv2, model->envp, model);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid;
	t_model	*model;
	int		res;

	res = 0;
	validations(argc, argv, pipe(pipefd));
	model = create_and_init_model(argv, pipefd, envp);
	if (!model)
		return (1);
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		res = (1);
	}
	if (!res && process_mediator(pid, model))
		res = 1;
	clean_up_resources(model);
	return (res);
}
