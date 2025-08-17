/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:44:59 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/21 16:44:59 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_putnbr(int n)
{
	char			c;
	static size_t	char_c;

	char_c = 0;
	if (n / 10 != 0)
		ft_putnbr(n / 10);
	if (n < 0)
		c = '0' + (n % 10) * (-1);
	else
		c = '0' + n % 10;
	if (n / 10 == 0 && n < 0)
	{
		write(1, "-", 1);
		char_c++;
	}
	write(1, &c, 1);
	return (++char_c);
}

size_t	ft_putuint(unsigned int n)
{
	char			c;
	static size_t	char_c;

	char_c = 0;
	if (n / 10 != 0)
		ft_putuint(n / 10);
	c = '0' + n % 10;
	write(1, &c, 1);
	return (++char_c);
}
