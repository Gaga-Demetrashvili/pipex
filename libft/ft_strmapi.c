/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:05:20 by gdemetra          #+#    #+#             */
/*   Updated: 2025/08/15 20:38:18 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*modified_str;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	modified_str = ft_calloc(len + 1, sizeof(char));
	if (!modified_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		modified_str[i] = f(i, s[i]);
		i++;
	}
	return (modified_str);
}

char	ft_delegate_mapi(unsigned int i, char c)
{
	return (c + (i * 0) + 1);
}
