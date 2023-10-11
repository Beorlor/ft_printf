/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:26:57 by jedurand          #+#    #+#             */
/*   Updated: 2023/10/11 14:17:05 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_nlen(t_format *format, unsigned long long n)
{
	int	i;

	i = 0;
	if (format->precision == -2 || (format->precision == 0 && n == 0))
		return (0);
	if (n == 0)
		return (5);
	while (n)
	{
		n /= 16;
		i++;
	}
	return (i);
}

static int	ft_putnb(t_format *format, unsigned long long n)
{
	char	c;
	int		count;

	if (format->precision == -2 || (format->precision == 0 && n == 0))
		return (0);
	if (n < 16)
	{
		c = "0123456789abcdef"[n % 16];
		write(1, &c, 1);
		return (1);
	}
	count = ft_putnb(format, n / 16);
	c = "0123456789abcdef"[n % 16];
	count += write(1, &c, 1);
	return (count);
}

static int	zero_flag_case(t_format *format, int *size, unsigned long long adr)
{
	int	count;

	count = 0;
	if (adr != 0)
	{
		count += write(1, "0x", 2);
		*size += 2;
	}
	count += print_zero((format->width) - *size);
	return (count);
}

static int	no_zero_flag_case(t_format *format, int *size, int *nb_total_size,
			unsigned long long adr)
{
	int	count;

	count = 0;
	if (format->precision > *size && format->precision >= 0)
	{
		*nb_total_size = format->precision;
		if (adr != 0)
		{
			(*nb_total_size) += 2;
			(*size) += 2;
		}
		if (format->width > *nb_total_size && format->minus_flag == 0)
			count += print_space((format->width) - *nb_total_size);
	}
	else
	{
		if (adr != 0)
			(*size) += 2;
		*nb_total_size = *size;
		if (format->width > *size && format->minus_flag == 0)
			count += print_space((format->width) - *size);
	}
	return (count);
}

int	print_adress(t_format *format, void *adr)
{
	int					count;
	int					size;
	int					nb_total_size;
	unsigned long long	adr_value;

	count = 0;
	adr_value = (unsigned long long) adr;
	size = ft_nlen(format, adr_value);
	if (format->zero_flag == 1)
		count += zero_flag_case(format, &size, adr_value);
	if (format->zero_flag == 0)
	{
		count += no_zero_flag_case(format, &size, &nb_total_size, adr_value);
		if (adr_value != 0)
			count += write(1, "0x", 2);
		if (nb_total_size > size && format->precision >= 0)
			count += print_zero(nb_total_size - size);
	}
	if (adr_value == 0)
		count += write(1, "(nil)", 5);
	else
		count += ft_putnb(format, adr_value);
	if (format->minus_flag == 1)
		count += print_space((format->width) - nb_total_size);
	return (count);
}
