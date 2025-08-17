/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:18:03 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/17 20:19:46 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	numchr;

	if (n / 10 != 0)
	{
		ft_putnbr_fd(n / 10, fd);
	}
	if (n < 0)
		numchr = 48 + n % 10 * (-1);
	else
		numchr = 48 + n % 10;
	if (n / 10 == 0 && n % 10 < 0)
	{
		write(fd, "-", 1);
		write(fd, &numchr, 1);
	}
	else
		write(fd, &numchr, 1);
}

// int main()
// {
//     int num = 0;
//     ft_putnbr_fd(num, 1);
//     return (0);
// }