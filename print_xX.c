#include "ft.h"

static int	ft_nlen(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 16;
		i++;
	}
	return (i);
}

static int	ft_putnb(t_format *format, unsigned int n)
{
	char	c;
	int		count;

	if (n < 16)
	{
		if (format->specifier == 'x')
			c = "0123456789abcdef"[n % 16];
		if (format->specifier == 'X')
			c = "0123456789ABCDEF"[n % 16];
		write(1, &c, 1);
		return (1);
	}
	count = ft_putnb(format, n / 16);
	if (format->specifier == 'x')
		c = "0123456789abcdef"[n % 16];
	if (format->specifier == 'X')
		c = "0123456789ABCDEF"[n % 16];
	count += write(1, &c, 1);
	return (count);
}

static int	zero_flag_case(t_format *format, int *size)
{
	int	count;

	count = 0;
	if (format->hash_flag == 1)
	{
		if (format->specifier == 'x')
			count += write(1, "0x", 2);
		if (format->specifier == 'x')
			count += write(1, "0X", 2);
		*size += 2;
	}
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
		if (format->hash_flag == 1)
		{
			(*nb_total_size)++;
			(*size)++;
		}
		if (format->width > *nb_total_size && format->minus_flag == 0)
			count += print_space((format->width) - *nb_total_size);
	}
	else
	{
		if (format->hash_flag == 1)
			(*size)++;
		*nb_total_size = *size;
		if (format->width > *size && format->minus_flag == 0)
			count += print_space((format->width) - *size);
	}
	return (count);
}

int	print_x_numb(t_format *format, unsigned int n)
{
	int	count;
	int	size;
	int	nb_total_size;

	count = 0;
	size = ft_nlen(n);
	if (format->zero_flag == 1)
		count += zero_flag_case(format, &size);
	if (format->zero_flag == 0)
	{
		count += no_zero_flag_case(format, &size, &nb_total_size);
		if (format->hash_flag == 1)
		{
			if (format->specifier == 'x')
				count += write(1, "0x", 2);
			if (format->specifier == 'x')
				count += write(1, "0X", 2);
		}
		if (nb_total_size > size && format->precision >= 0)
			count += print_zero(nb_total_size - size);
	}
	count += ft_putnb(format, n);
	if (format->minus_flag == 1)
		count += print_space((format->width) - nb_total_size);
	return (count);
}
