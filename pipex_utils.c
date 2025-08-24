/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:34:58 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/24 00:01:09 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *file_name, t_model *model, int is_rdonly)
{
	int	fd;

	if (is_rdonly)
		fd = open(file_name, O_RDONLY);
	else
		fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		ft_error_exit(file_name, ": No such file or directory\n", model, 1);
	return (fd);
}

t_model	*create_and_init_model(char **argv, int *pipefd, char **envp)
{
	t_model	*model;

	model = (t_model *)malloc(sizeof(t_model));
	if (!model)
		return (NULL);
	model->infile_name = argv[1];
	model->cmdv1 = ft_split(argv[2], ' ');
	model->cmdv2 = ft_split(argv[3], ' ');
	model->outfile_name = argv[4];
	model->read_end_of_pipe = pipefd[0];
	model->write_end_of_pipe = pipefd[1];
	model->envp = envp;
	return (model);
}

char	**paths_arr(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			paths = ft_split(envp[i] + 5, ':');
		i++;
	}
	if (!paths)
		ft_printf("Error\nPATH env variable does not exist");
	return (paths);
}

char	*find_path(char **cmdv, char **envp)
{
	int		i;
	char	*path;
	char	**paths;
	char	*c;

	i = 0;
	paths = paths_arr(envp);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		c = ft_strjoin(paths[i], "/");
		path = ft_strjoin(c, cmdv[0]);
		free(c);
		if (0 == access(path, X_OK))
		{
			free_arr(paths);
			return (path);
		}
		else
			free(path);
		i++;
	}
	free_arr(paths);
	return (NULL);
}
