/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:41:33 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/27 21:24:46 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	validations_b(int argc, char **argv)
{
	int	i;

	if (argc < 5)
	{
		ft_printf("pipex: program should have at least 4 args");
		exit(1);
	}
	if (ft_strlen(argv[1]) == 0 || ft_strlen(argv[argc - 1]) == 0)
	{
		ft_printf("pipex: filename is empty or whitespace");
		exit(1);
	}
	i = 1;
	while (i < argc)
	{
		if (ft_strlen(argv[i]) == 0 || argv[i][0] == ' ')
		{
			ft_printf("pipex: cmd is empty or whitespace");
			exit(1);
		}
		i++;
	}
}
