#include "ft.h"

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

//make a real count
static void	print_hex(unsigned long long adr, int *count)
{
	char	hex_digit;

	if (adr > 15)
        print_hex(adr / 16, count);
	hex_digit = "0123456789abcdef"[adr % 16];
    count += write(1, &hex_digit, 1);
}

//if adress is NULL ??
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
