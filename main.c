/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:03:38 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/17 15:03:14 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	create_pipe(int infile_fd, int outfile_fd)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe error");
		return (1);
	}
}

// int	main(int argc, char **argv, char **envp)
int	main(int argc, char **argv)
{
	int	infile_fd;
	int	outfile_fd;

	if (argc != 5)
	{
		ft_printf("Error\nProgram should take 4 args");
		return (1);
	}
	infile_fd = open_file(argv[1], 1);
	if (infile_fd < 0)
		return (1);
	outfile_fd = open_file(argv[4], 0);
	if (outfile_fd < 0)
		return (1);
	create_pipe(infile_fd, outfile_fd);
	return (0);
}
