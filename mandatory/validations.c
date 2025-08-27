/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:34:58 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/26 19:02:26 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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
		ft_printf("pipex: arg is empty or has whitespace\n");
		exit(1);
	}
	if (pipe_res == -1)
	{
		perror("pipex: pipe creation error\n");
		exit(1);
	}
}
