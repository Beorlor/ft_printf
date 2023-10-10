#include <stdio.h>

int main(void)
{
    printf("%p\n", "salut");
    printf("%20p\n", "salut");
    printf("%020p\n", "salut");
    printf("%.20p\n", "salut");
    printf("%30.20p\n", "salut");
    printf("%-20p\n", "salut");
}