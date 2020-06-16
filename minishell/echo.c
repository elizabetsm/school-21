#include <unistd.h> 
 
 void	ft_echo(char *name)
 {
	int i = 0;
	while (name[i] != '\0')
	{
		write(1, &name[i], 1);
		i++;
	}
 }