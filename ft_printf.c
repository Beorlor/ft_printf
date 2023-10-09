#include "ft.h"

/*void testing(t_format *fmt)
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
}*/

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
		count = print_adress(va_arg(ap, void *));
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
	//ft_printf("%8.4u 5\n", 42);
	//ft_printf("%#08x 5\n", 42);
	//ft_printf("%#8.3X 5\n", 42);
	ft_printf("%d\n", -2147483648);
	ft_printf("%d\n", -2);
	return(0);
}
