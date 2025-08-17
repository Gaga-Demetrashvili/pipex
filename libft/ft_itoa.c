/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:20:24 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/13 17:20:24 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_numlen(int num)
{
	size_t	len;

	if (num == 0)
		return (1);
	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 10;
	}
	return (len);
}

void	ft_numstr(int n, char *dest, size_t len)
{
	if (n / 10 != 0)
	{
		ft_numstr(n / 10, dest, len - 1);
	}
	if (len - 1 == 0 && n < 0)
		dest[len - 1] = '-';
	if (n < 0)
		dest[len] = (n % 10) * (-1) + 48;
	else
		dest[len] = n % 10 + 48;
}

void	ft_initialize_str(char *str, size_t len)
{
	while (len-- > 0)
	{
		str[len] = '\0';
	}
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*dest;

	len = ft_numlen(n);
	if (n < 0)
		len++;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	ft_initialize_str(dest, len + 1);
	ft_numstr(n, dest, len - 1);
	return (dest);
}
