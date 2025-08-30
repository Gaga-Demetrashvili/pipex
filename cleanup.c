/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 22:51:33 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/30 16:01:24 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_empty_or_whitespace(char *str)
{
	int	i;

	if (ft_strlen(str) == 0)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	free_cmdv_arr(char ***arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free_arr(arr[i]);
		i++;
	}
	free(arr);
}

void	clean_up_resources(t_model model)
{
	free_cmdv_arr(model.cmdv_arr);
	free_arr(model.cmds_arr);
}

void	ft_error_exit(char *str, char *str2, t_model model, int status)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		write(2, "pipex: ", 7);
		write(2, str2, ft_strlen(str2));
		exit(1);
	}
	write(2, "pipex: ", 7);
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
	write(2, str2, ft_strlen(str2));
	write(2, "\n", 1);
	clean_up_resources(model);
	exit(status);
}
