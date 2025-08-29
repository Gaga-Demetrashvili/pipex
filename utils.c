/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:34:58 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/29 22:23:40 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "pipex.h"

int	open_file(char *file_name, t_model model, int is_rdonly)
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

void	execute_cmd(char **cmdv, char **envp, t_model model)
{
	int		i;
	char	*path;

	i = 0;
	path = find_path(cmdv, envp);
	if (!path)
		ft_error_exit(cmdv[0], ": command not found\n", model, 127);
	if (execve(path, cmdv, envp) == -1)
	{
		perror("execv failed");
		free(path);
		clean_up_resources(model);
		exit(1);
	}
}

static char	**paths_arr(char **envp)
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
