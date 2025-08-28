/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:41:33 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/28 20:27:03 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*st1;
	unsigned char	*st2;
	size_t			i;
	int				res;

	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	i = 0;
	res = 0;
	while (st1[i] && st2[i])
	{
		if (st1[i] == st2[i])
			i++;
		else
			break ;
	}
	if (st1[i] == st2[i])
		return (res);
	else if (st1[i] > st2[i])
		res = 1;
	else
		res = -1;
	return (res);
}

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
	i = 2;
	while (i < argc)
	{
		if (is_empty_or_whitespace(argv[i]))
		{
			ft_printf("pipex: cmd is empty or whitespace");
			exit(1);
		}
		i++;
	}
}
