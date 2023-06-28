#include "../includes/libft.h"

void	ft_swap_bin(char *a, char *b)
{
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}