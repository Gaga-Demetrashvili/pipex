/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:29:55 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/07 16:14:28 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

// #include <string.h>
// #include <unistd.h>

// void	ft_print_arr(char *str)
// {
// 	char	*s;

// 	s = str;
// 	while (*s)
// 	{
// 		write(1, s, 1);
// 		s++;
// 	}
// }

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	return (ft_memmove(dest, src, n));
}

// int	main(void)
// {
// 	char dest[] = "1234";
// 	char source[] = "1234";
// 	ft_memcpy(dest + 1, dest, 3);
// 	ft_print_arr(dest);
// 	write(1, "\n", 1);
// 	memcpy(source + 1, source, 3);
// 	ft_print_arr(source);
// 	return (0);
// }