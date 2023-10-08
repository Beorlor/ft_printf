#include "ft.h"

static void	list_reset(t_format *format)
{
	format->minus_flag = 0;
	format->zero_flag = 0;
	format->hash_flag = 0;
	format->space_flag = 0;
	format->plus_flag = 0;
	format->width = -1;
	format->precision = -1;
	format->specifier = 0;
}

static const char	*get_num_width(t_format *format, const char *str, int *error, va_list ap)
{
	if (*str == '*')
		format->width = va_arg(ap, int);
	else
	{
		format->width = ft_atoi(str);
		while (is_digit(*str))
			str++;
		if (!is_specifier(*str) && *str != '.')
		{
			*error = 1;
			return (str);
		}
		return (--str);
	}
	return (str);
}

static const char	*get_num_dot(t_format *format, const char *str, int *error, va_list ap)
{
	++str;
	if (is_specifier(*str))
		format->precision = 0;
	if (*str == '*')
		format->precision = va_arg(ap, int);
	else
	{
		format->precision = ft_atoi(str);
		while (is_digit(*str))
			str++;
		if (!is_specifier(*str))
		{
			*error = 1;
			return (str);
		}
		return (--str);
	}
	return (str);
}

const char	*fill_list(t_format *format, const char *str, int *error, va_list ap)
{
	list_reset(format);
	while (!is_specifier(*str))
	{
		if (*str == '0')
			format->zero_flag = 1;
		else if (is_digit(*str) || *str == '*')
			str = get_num_width(format, str, error, ap);
		else if (*str == '.')
			str = get_num_dot(format, str, error, ap);
		else if (*str == '-')
			format->minus_flag = 1;
		else if (*str == '#')
			format->hash_flag = 1;
		else if (*str == ' ')
			format->space_flag = 1;
		else if (*str == '+')
			format->plus_flag = 1;
		else
			*error = 1;
		if (*error == 1)
			return (--str);
		str++;
	}
	format->specifier = *str;
	return (str);
}

void	list_processing(t_format *format)
{
	if (format->specifier == 'f' && format->precision == -1)
		format->precision = 6;
	if (format->zero_flag == 1 && format->minus_flag == 1)
		format->zero_flag = 0;
	if (format->space_flag == 1 && format->plus_flag == 1)
		format->space_flag = 0;
	if (format->zero_flag == 1 && format->precision >= 0
		&& (format->specifier == 'd' || format->specifier == 'i'
			|| format->specifier == 'u' || format->specifier == 'x'
				|| format->specifier == 'X'))
		format->zero_flag = 0;
}
