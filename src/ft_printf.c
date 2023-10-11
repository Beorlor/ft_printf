/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:09:59 by jedurand          #+#    #+#             */
/*   Updated: 2023/10/10 13:10:45 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_space(int i)
{
	int	count;

	count = 0;
	while (i-- > 0)
		count += write(1, " ", 1);
	return (count);
}

int	print_zero(int i)
{
	int	count;

	count = 0;
	while (i-- > 0)
		count += write(1, "0", 1);
	return (count);
}

int	print_arg(t_format *format, va_list ap)
{
	int	count;

	count = 0;
	list_processing(format);
	if (format->specifier == 'c')
		count = print_char(format, va_arg(ap, int));
	if (format->specifier == 's')
		count = print_string(format, va_arg(ap, char *));
	if (format->specifier == 'p')
		count = print_adress(format, va_arg(ap, void *));
	if (format->specifier == 'd' || format->specifier == 'i')
		count = print_numb(format, (long)va_arg(ap, int));
	if (format->specifier == 'u')
		count = print_u_numb(format, va_arg(ap, unsigned int));
	if (format->specifier == 'x' || format->specifier == 'X')
		count = print_x_numb(format, va_arg(ap, unsigned int));
	if (format->specifier == '%')
		count = print_char(format, '%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list		ap;
	int			count;
	t_format	*format;
	int			error;

	va_start(ap, str);
	format = (t_format *)malloc(sizeof(t_format));
	count = 0;
	while (*str != '\0')
	{
		if (*str == '%')
		{
			error = 0;
			str = fill_list(format, (++str), &error, ap);
			if (!error)
				count += print_arg(format, ap);
		}
		else
			count += write(1, str, 1);
		str++;
	}
	free(format);
	va_end(ap);
	return (count);
}
