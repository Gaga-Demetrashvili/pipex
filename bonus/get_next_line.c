/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:13:52 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/28 20:08:40 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"

static void	append(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*lastnod;

	if (!buf[0])
		return (free(buf));
	new_node = (t_list *)malloc(sizeof(t_list));
	if (NULL == new_node)
	{
		free(buf);
		return (clear_list(list));
	}
	lastnod = get_last_node(*list);
	if (NULL == lastnod)
		*list = new_node;
	else
		lastnod->next = new_node;
	new_node->content = buf;
	new_node->next = NULL;
}

static void	polish_list(t_list **list)
{
	t_list	*lastnod;
	int		i;
	int		j;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (clear_list(list));
	lastnod = get_last_node(*list);
	i = 0;
	j = 0;
	while (lastnod->content[i] && lastnod->content[i] != '\n')
		i++;
	while (lastnod->content[i] && lastnod->content[++i])
		buf[j++] = lastnod->content[i];
	buf[j] = '\0';
	clear_list(list);
	append(list, buf);
}

static char	*grab_new_line(t_list **list, char *line)
{
	size_t	count_bytes;

	count_bytes = count_chars(*list);
	line = (char *)malloc(count_bytes + 1);
	if (!line)
	{
		clear_list(list);
		return (NULL);
	}
	copy_str(*list, line);
	return (line);
}

static void	create_list(t_list **list, int fd)
{
	ssize_t	readbytes;
	char	*buf;

	readbytes = 0;
	while (!found_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (NULL == buf)
			return (clear_list(list));
		readbytes = read(fd, buf, BUFFER_SIZE);
		if (!readbytes)
		{
			free(buf);
			return ;
		}
		buf[readbytes] = '\0';
		append(list, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (read(fd, &line, 0) < 0)
	{
		clear_list(&list);
		return (NULL);
	}
	create_list(&list, fd);
	if (list == NULL)
		return (NULL);
	line = grab_new_line(&list, line);
	if (list == NULL)
		return (NULL);
	polish_list(&list);
	return (line);
}

// int	main(void)
// {
// 	int fd;
// 	char *line;

// 	fd = open("file.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	return (0);
// }