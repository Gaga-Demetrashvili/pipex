/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 22:17:16 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/29 22:20:52 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include "../pipex.h"

void	heredoc_logic(char *limiter, char *heredoc_infile_name)
{
	int		stdin_fd;
	char	*line;
	char	*limiter_with_n;
	char	tmp_file_fd;

	stdin_fd = 0;
	tmp_file_fd = open(heredoc_infile_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	limiter_with_n = ft_strjoin(limiter, "\n");
	ft_printf("> ");
	line = get_next_line(stdin_fd);
	while (line && ft_strcmp(line, limiter_with_n))
	{
		write(tmp_file_fd, line, ft_strlen(line));
		free(line);
		ft_printf("> ");
		line = get_next_line(stdin_fd);
	}
	close(tmp_file_fd);
	free(limiter_with_n);
	if (line)
		free(line);
}
