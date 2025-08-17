/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:37:16 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/12 21:06:15 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

// #include <stdio.h>
// #include <string.h>

// size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
// {
// 	char		*d;
// 	const char	*s = src;
// 	size_t		n;

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	src_len = 0;
	while (src[src_len])
		src_len++;
	if (size == 0)
		return (src_len);
	i = 0;
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

// int	main(void)
// {
// 	char	*dest;

// 	memset(dest, 0, 15);
// 	memset(dest, 'r', 6);
// 	ft_strlcpy(dest, "lorem ipsum dolor sit amet", 15);
// 	return (0);
// }