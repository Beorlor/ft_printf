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

static const char	*get_num_width(t_format *format, const char *str, int *error, va_list var)
{
	if (*str == '*')
		format->width = va_arg(var, int);
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

static const char	*get_num_dot(t_format *format, const char *str, int *error, va_list var)
{
	++str;
	if (is_specifier(*str))
		format->precision = 0;
	if (*str == '*')
		format->precision = va_arg(var, int);
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

//wrong order verif
//manque de robustesse (peut etre pas enfaite)
const char	*fill_list(t_format *format, const char *str, int *error, va_list var)
{
	list_reset(format);
	while (!is_specifier(*str))
	{
		if (*str == '0')
			format->zero_flag = 1;
		else if (is_digit(*str) || *str == '*')
			str = get_num_width(format, str, error, var);
		else if (*str == '.')
			str = get_num_dot(format, str, error, var);
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
