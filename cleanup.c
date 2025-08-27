/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 22:51:33 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/26 19:07:51 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	write(2, str2, ft_strlen(str2));
	clean_up_resources(model);
	exit(status);
}
