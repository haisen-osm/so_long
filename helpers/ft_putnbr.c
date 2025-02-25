#include "../so_long.h"

void ft_putnbr(int n)
{
	long num;

	num = n;
	if (num > 9)
		ft_putnbr(num / 10);
	ft_putchar(num % 10 + 48);
}