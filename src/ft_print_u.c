/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:27:12 by jedurand          #+#    #+#             */
/*   Updated: 2023/10/11 14:17:08 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_nlen(t_format *format, unsigned int n)
{
	int	i;

	i = 0;
	if (format->precision == -2 || (format->precision == 0 && n == 0))
		return (0);
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	ft_putnb(t_format *format, unsigned int n)
{
	char	c;
	int		count;

	if (format->precision == -2 || (format->precision == 0 && n == 0))
		return (0);
	if (n < 10)
	{
		c = n + '0';
		write(1, &c, 1);
		return (1);
	}
	count = ft_putnb(format, n / 10);
	c = (n % 10) + '0';
	count += write(1, &c, 1);
	return (count);
}

static int	zero_flag_case(t_format *format, int *size)
{
	int	count;

	count = 0;
	count += print_zero((format->width) - *size);
	return (count);
}

static int	no_zero_flag_case(t_format *format, int *size, int *nb_total_size)
{
	int	count;

	count = 0;
	if (format->precision > *size && format->precision >= 0)
	{
		*nb_total_size = format->precision;
		if (format->width > *nb_total_size && format->minus_flag == 0)
			count += print_space((format->width) - *nb_total_size);
	}
	else
	{
		*nb_total_size = *size;
		if (format->width > *size && format->minus_flag == 0)
			count += print_space((format->width) - *size);
	}
	return (count);
}

int	print_u_numb(t_format *format, unsigned int n)
{
	int	count;
	int	size;
	int	nb_total_size;

	count = 0;
	size = ft_nlen(format, n);
	if (format->zero_flag == 1)
		count += zero_flag_case(format, &size);
	if (format->zero_flag == 0)
	{
		count += no_zero_flag_case(format, &size, &nb_total_size);
		if (nb_total_size > size && format->precision >= 0)
			count += print_zero(nb_total_size - size);
	}
	count += ft_putnb(format, n);
	if (format->minus_flag == 1)
		count += print_space((format->width) - nb_total_size);
	return (count);
}
