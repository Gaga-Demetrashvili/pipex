/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:13:48 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/28 20:08:36 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"

t_list	*get_last_node(t_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	clear_list(t_list **list)
{
	t_list	*temp;

	if (!list)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = temp;
	}
	*list = NULL;
}

int	found_newline(t_list *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

int	count_chars(t_list *list)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		list = list->next;
	}
	return (len);
}

void	copy_str(t_list *list, char *line)
{
	int	i;
	int	j;

	i = 0;
	while (list)
	{
		j = 0;
		while (list->content[j])
		{
			if (list->content[j] == '\n')
			{
				line[i++] = '\n';
				line[i] = '\0';
				return ;
			}
			line[i++] = list->content[j++];
		}
		list = list->next;
	}
	line[i] = '\0';
}
