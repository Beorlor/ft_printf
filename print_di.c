#include "ft.h"

static int	ft_nlen(long n, int *sign)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		*sign = -1;
	else
		*sign = 1;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	ft_putnb(long n)
{
	char	c;
	int		count;

	if (n < 0)
		n = -n;
	if (n < 10)
	{
		c = n + '0';
		write(1, &c, 1);
		return (1);
	}
	count = ft_putnb(n / 10);
	c = (n % 10) + '0';
	count += write(1, &c, 1);
	return (count);
}

static int	zero_flag_case(t_format *format, int *size, int sign)
{
	int	count;

	count = 0;
	if (sign == -1)
	{
		count += write(1, "-", 1);
		count += print_zero((format->width) - ++(*size));
	}
	else if (format->plus_flag == 1)
	{
		count += write(1, "+", 1);
		count += print_zero((format->width) - ++(*size));
	}
	else if (format->space_flag == 1)
	{
		count += write(1, " ", 1);
		count += print_zero((format->width) - ++(*size));
	}
	else
		count += print_zero((format->width) - *size);
	return (count);
}

static int	no_zero_flag_case(t_format *format, int *size, int *nb_total_size, int sign)
{
	int	count;

	count = 0;
	if (format->precision > *size && format->precision >= 0)
	{
		*nb_total_size = format->precision;
		if (sign == -1 || format->plus_flag == 1 || format->space_flag == 1)
		{
			(*nb_total_size)++;
			(*size)++;
		}
		if (format->width > *nb_total_size && format->minus_flag == 0)
			count += print_space((format->width) - *nb_total_size);
	}
	else
	{
		if (sign == -1 || format->plus_flag == 1 || format->space_flag == 1)
			(*size)++;
		*nb_total_size = *size;
		if (format->width > *size && format->minus_flag == 0)
			count += print_space((format->width) - *size);
	}
	return (count);
}

int	print_numb(t_format *format, long n)
{
	int	count;
	int	size;
	int	sign;
	int	nb_total_size;

	count = 0;
	size = ft_nlen(n, &sign);
	if (format->zero_flag == 1)
		count += zero_flag_case(format, &size, sign);
	if (format->zero_flag == 0)
	{
		count += no_zero_flag_case(format, &size, &nb_total_size, sign);
		if (sign == -1)
			count += write(1, "-", 1);
		else if (format->plus_flag == 1)
			count += write(1, "+", 1);
		else if (format->space_flag == 1)
			count += write(1, " ", 1);
		if (nb_total_size > size && format->precision >= 0)
			count += print_zero(nb_total_size - size);
	}
	count += ft_putnb(n);
	if (format->minus_flag == 1)
		count += print_space((format->width) - nb_total_size);
	return (count);
}
