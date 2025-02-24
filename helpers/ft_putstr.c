#include "../so_long.h"

void ft_putstr(char *str)
{
	size_t i = 0;
	if (!str)
		return;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}