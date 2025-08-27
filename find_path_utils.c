/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:45:04 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/26 22:30:55 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
