/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:43:17 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/07 12:36:23 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>

// void	ft_printarr(char *arr, size_t size)
// {
// 	int	i;

// 	i = 0;
// 	while (i < size)
// 	{
// 		write(1, (arr + i), 1);
// 		i++;
// 	}
// 	write(1, "\n", 1);
// }

void	*ft_memset(void *s, int value, size_t n)
{
	while (n-- > 0)
		*(unsigned char *)(s + n) = value & 0xFF;
	return (s);
}

// int	main(void)
// {
// 	char str1[5];
// 	char str2[5];
// 	ft_memset(str1, 65, 4);
// 	ft_printarr(str1, 5);
// 	write(1, "\n", 1);
// 	memset(str2, 65, 4);
// 	ft_printarr(str2, 5);

// 	return (0);
// }