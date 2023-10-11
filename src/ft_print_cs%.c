/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_cs%.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:16:03 by jedurand          #+#    #+#             */
/*   Updated: 2023/10/10 13:20:20 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//% use print_char
int	print_char(t_format *format, int c)
{
	int	count;

	count = 0;
	if (format->width > 1 && format->minus_flag == 0)
	{
		if (format->zero_flag == 1)
			count += print_zero((format->width) - 1);
		else
			count += print_space((format->width) - 1);
	}
	count += write(1, &c, 1);
	if (format->minus_flag == 1)
		count += print_space((format->width) - 1);
	return (count);
}

int	add_width(t_format *format, int size)
{
	int	count;

	count = 0;
	if (format->zero_flag == 1)
		count += print_zero((format->width) - size);
	else
		count += print_space((format->width) - size);
	return (count);
}

int	print_string(t_format *format, char *str)
{
	int	count;
	int	size;
	int	is_null;

	count = 0;
	is_null = 0;
	if (str == NULL)
	{
		str = "(null)";
		is_null = 1;
	}
	size = ft_slen(str);
	if (format->precision < size && format->precision >= 0)
		size = format->precision;
	if (is_null == 1 && size < 6)
		size = 0;
	if (format->width > size && format->minus_flag == 0)
		count += add_width(format, size);
	count += write(1, str, size);
	if (format->minus_flag == 1)
		count += print_space((format->width) - size);
	return (count);
}
