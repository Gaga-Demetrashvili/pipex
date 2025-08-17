/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:36:32 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/07 16:19:07 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

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

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (dest == NULL && src == NULL)
		return (dest);
	d = (char *)dest;
	s = (const char *)src;
	if (d > s || s - 1 < d)
		while (n--)
			*(d + n) = *(s + n);
	else
		while (n--)
			*d++ = *s++;
	return (dest);
}

// int	main(void)
// {
// 	char dest[] = "1234"; // 23
// 	char src[] = "1234";

// 	ft_memmove(dest, dest + 1, 3);
// 	ft_printarr(dest, 5);
// 	write(1, "\n", 1);
// 	memmove(src, src + 1, 3);
// 	ft_printarr(src, 5);
// 	return (0);
// }