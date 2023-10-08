#include "ft.h"

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
