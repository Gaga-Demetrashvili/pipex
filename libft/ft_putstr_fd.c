/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:51:25 by gdemetra          #+#    #+#             */
/*   Updated: 2025/07/26 18:03:34 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(const char *s, int fd)
{
	size_t	strlen;

	strlen = ft_strlen(s);
	write(fd, s, strlen);
}

// int	main(void)
// {
// 	char *str = "Gaga Demetrashvili";
// 	ft_putstr_fd(str, 1);
// 	return (0);
// }