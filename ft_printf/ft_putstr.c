/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:42:50 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/21 16:42:50 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (*(str + i))
		i++;
	return (i);
}

size_t	ft_putstr(char *str)
{
	char	*null_case;
	size_t	char_c;

	if (!str)
	{
		null_case = "(null)";
		char_c = ft_strlen(null_case);
		write(1, null_case, char_c);
		return (char_c);
	}
	char_c = ft_strlen(str);
	write(1, str, char_c);
	return (char_c);
}
