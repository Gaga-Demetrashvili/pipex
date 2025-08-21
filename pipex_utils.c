/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:34:58 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/21 22:00:58 by gdemetra         ###   ########.fr       */
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
