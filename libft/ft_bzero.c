/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:13:38 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/04 12:13:38 by gdemetra         ###   ########.fr       */
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
// 		write(1, (arr + i++), 1);
// 	}
// 	write(1, "\n", 1);
// }

void	ft_bzero(void *s, size_t n)
{
	size_t	num;

	num = 0;
	while (num < n)
		*(unsigned char *)(s + num++) = '\0';
}

// int	main(void)
// {
// 	char str1[5] = {'B', 'B', 'B', 'B', 'B'};
// 	char str2[5] = {'B', 'B', 'B', 'B', 'B'};
// 	ft_bzero(str1, 3);
// 	ft_printarr(str1, 5);
// 	write(1, "\n", 1);
// 	bzero(str2, 3);
// 	ft_printarr(str2, 5);

// 	return (0);
// }