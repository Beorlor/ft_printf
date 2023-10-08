#include "ft.h"

//if (specifier == 'c')
//		count += print_char(va_arg(var, int));

void testing(t_format *fmt)
{
    if (!fmt)
    {
        printf("Structure pointer is NULL!\n");
        return;
    }

    printf("Contents of t_format structure:\n");
    printf("minus_flag: %d\n", fmt->minus_flag);
    printf("zero_flag : %d\n", fmt->zero_flag);
    printf("hash_flag : %d\n", fmt->hash_flag);
    printf("space_flag: %d\n", fmt->space_flag);
    printf("plus_flag : %d\n", fmt->plus_flag);
    printf("width     : %d\n", fmt->width);
    printf("precision : %d\n", fmt->precision);
    printf("specifier : %c\n", fmt->specifier);
}

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

int	print_string(t_format *format, char *str)
{
	int	count;
	int	size;

	count = 0;
	size = ft_slen(str);
	if (format->precision < size && format->precision >= 0)
		size = format->precision;
	if (format->width > size && format->minus_flag == 0)
	{
		if (format->zero_flag == 1)
			count += print_zero((format->width) - size);
		else
			count += print_space((format->width) - size);
	}
	count += write(1, str, size);
	if (format->minus_flag == 1)
		count += print_space((format->width) - size);
	return (count);
}

static void	print_hex(unsigned long long adr, int *count)
{
	char	hex_digit;

	if (adr > 15)
        print_hex(adr / 16, count);
	hex_digit = "0123456789abcdef"[adr % 16];
    count += write(1, &hex_digit, 1);
}

int	print_adress(void *adr)
{
	int	count;
	unsigned long long adr_value;

	count = 0;
	adr_value = (unsigned long long) adr;
	count += write(1, "0x", 2);
	if (adr_value == 0)
		count += write(1, "0", 1);
	else
			print_hex(adr_value, &count);
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
		count = print_adress(va_arg(ap, void *));
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int	count;
	t_format *format;
	int error;

	va_start(ap, str);
	format = (t_format *)malloc(sizeof(t_format));
	count = 0;
	while (*str != '\0')
	{
		if (*str == '%')
		{
			error = 0;
			str = fill_list(format, (++str), &error, ap);
			testing(format);
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

int	main(void)
{
	//ft_printf("%c salut  %c", 97, 98);
	ft_printf("%p   5\n", "salut");
	return(0);
}
