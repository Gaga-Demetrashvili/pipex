/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prhex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:40:01 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/21 15:40:01 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// a_case - param for controlling case (1 - upper, 0 - lower)
static size_t	ft_puthex(unsigned int n, size_t a_case)
{
	static char		*hex;
	char			c;
	static size_t	char_c;

	hex = "0123456789abcdef";
	char_c = 0;
	if (n / 16 != 0)
		ft_puthex(n / 16, a_case);
	if (a_case && n % 16 > 9)
		c = hex[n % 16] - 32;
	else
		c = hex[n % 16];
	write(1, &c, 1);
	return (++char_c);
}

size_t	ft_putp(unsigned long p)
{
	static char		*hex;
	char			c;
	static size_t	char_c;
	char			*null_case;

	hex = "0123456789abcdef";
	char_c = 0;
	if (p == 0)
		return (ft_putstr(null_case = "(nil)"));
	if (p / 16 != 0)
		ft_putp(p / 16);
	c = hex[p % 16];
	if (p / 16 == 0)
	{
		write(1, "0x", 2);
		char_c = +2;
	}
	write(1, &c, 1);
	return (++char_c);
}

size_t	ft_puthexhandler(unsigned int n, char t)
{
	size_t	char_c;

	if (t == 'x')
		char_c = ft_puthex(n, 0);
	else
		char_c = ft_puthex(n, 1);
	return (char_c);
}
