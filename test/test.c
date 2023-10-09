#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int *i = malloc(4);
	printf("%#-8.3x 5\n", 42);
	printf("%#8.3x 5\n", 42);
	return (0);
}
