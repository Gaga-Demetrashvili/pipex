/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:30:33 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/20 20:30:33 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_mediator(va_list args, char c)
{
	size_t	char_c;

	char_c = 0;
	if (c == 'c')
		char_c = ft_putchar(va_arg(args, int));
	else if (c == 's')
		char_c = ft_putstr(va_arg(args, char *));
	else if (c == 'p')
		char_c = ft_putp((unsigned long)va_arg(args, void *));
	else if (c == 'x' || c == 'X')
		char_c = ft_puthexhandler(va_arg(args, unsigned int), c);
	else if (c == 'i' || c == 'd')
		char_c = ft_putnbr(va_arg(args, int));
	else if (c == 'u')
		char_c = ft_putuint(va_arg(args, unsigned int));
	else if (c == '%')
		char_c = ft_putchar('%');
	return (char_c);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	i;
	size_t	char_c;

	va_start(args, str);
	i = 0;
	char_c = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			char_c += ft_mediator(args, str[i + 1]);
			i += 2;
		}
		while (str[i] && str[i] != '%')
		{
			char_c += ft_putchar(str[i]);
			i++;
		}
	}
	va_end(args);
	return (char_c);
}
