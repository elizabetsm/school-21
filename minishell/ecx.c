#include <unistd.h>
#include "minishell.h"
int main(int argc, char **argv, char **env)
{
	char *inp = malloc(sizeof(char *) * 10);
	pid_t pid = fork();
	// signal(SIGINT, proc_signal_handler);
	// ft_putchar('1');
	char *name = "/home/liza/minishell/echo.o";
	char *arg[] = {name, argv[0], NULL};
	if (pid == 0)
		execve(name, arg+1, env);
	else
		wait(&pid);
}