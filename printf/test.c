#include "libft/libft.h"


void	ftt_putstr(char* a)
{
	int i;
	i = 0;
	while(a[i] != '\0')
	{
		write(1, &a[i], 1);
		i++;
	}
	ft_putstr("world\n");
}

int main()
{
	ft_putstr("\033[1;34m");
	ftt_putstr("hello");
	ft_putstr("\033[0m");
	ft_putstr("world\n");
}