/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdemetra <gdemetra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:37:04 by gdemetra          #+#    #+#             */
/*   Updated: 2025/06/22 14:23:21 by gdemetra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

size_t	ft_puthexhandler(unsigned int n, char t);
int		ft_printf(const char *str, ...);
size_t	ft_putchar(char c);
size_t	ft_putnbr(int n);
size_t	ft_putstr(char *str);
size_t	ft_putuint(unsigned int n);
size_t	ft_putp(unsigned long p);

#endif