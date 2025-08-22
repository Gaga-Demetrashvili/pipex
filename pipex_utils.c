/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:34:58 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/22 22:26:33 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	validations(int argc, int pipe_res)
{
	if (argc != 5)
	{
		ft_printf("Error\nProgram should take 4 args");
		return (1);
	}
	if (pipe_res == -1)
	{
		perror("Error\nPipe error");
		return (1);
	}
	return (0);
}

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

t_model	*create_and_init_model(char **argv, int *pipefd, char **envp)
{
	t_model	*model;

	model = (t_model *)malloc(sizeof(t_model));
	if (!model)
		return (NULL);
	model->infile_name = argv[1];
	model->cmd1 = argv[2];
	model->cmd2 = argv[3];
	model->outfile_name = argv[4];
	model->read_end_of_pipe = pipefd[0];
	model->write_end_of_pipe = pipefd[1];
	model->envp = envp;
	model->paths = NULL;
	return (model);
}

void	free_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}