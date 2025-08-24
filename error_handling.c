/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 22:51:33 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/24 12:38:39 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	validations(int argc, char **argv, int pipe_res)
{
	if (argc != 5)
	{
		ft_printf("pipex: program should take 4 args\n");
		exit(1);
	}
	if (ft_strlen(argv[2]) == 0 || argv[2][0] == ' ' || ft_strlen(argv[3]) == 0
		|| argv[3][0] == ' ' || ft_strlen(argv[1]) == 0
		|| ft_strlen(argv[4]) == 0)
	{
		ft_printf("pipex: cmd is empty or has whitespace\n");
		exit(1);
	}
	if (pipe_res == -1)
	{
		perror("pipex: pipe creation error\n");
		exit(1);
	}
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

void	clean_up_resources(t_model *model)
{
	free_arr(model->cmdv1);
	free_arr(model->cmdv2);
	free(model);
}

void	ft_error_exit(char *str, char *str2, t_model *model, int status)
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
