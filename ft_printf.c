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

int	print_arg(t_format *format, va_list ap)
{
	int	count;

	count = 0;
	list_processing(format);
	if (format->specifier == 'c')
	{
		char test = va_arg(ap, int);
		printf("%c", test);
		//count += write(1, &test, 1);
	}
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
			//testing(format);
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
	ft_printf("%c salut  %c", 97, 98);
	return(0);
}
