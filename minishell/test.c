#include "minishell.h"
void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}
	/*
** Handles interruption signals on a running process
**
** @param		signo		The signal number
** @return		N/A
*/
void	proc_signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		// ft_putstr("\n");
		// printf("\n");
		ft_putchar('\n');
		ft_putchar('>');
		signal(SIGINT, proc_signal_handler);
	}
}

/*
** Handles interruption signals on the program
**
** @param		signo		The signal number
** @return		N/A
*/

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{

		ft_putchar('\n');
		ft_putchar('>');
		// display_prompt_msg();
		signal(SIGINT, signal_handler);
	}
}

char *vvod(t_struct *mini)
{
	int i = 0;
	// ft_putchar('2');
	mini->inp = malloc(sizeof(char *) * 10);
	char buf;
	while(read(0, &buf, 1) && buf != '\n')
	{
		mini->inp[i] = buf;
		i++;
	}
	mini->inp[i] = '\0';
	// printf("%s\n", inp);
}


char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*ss;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(ss = (char *)malloc(strlen(s1) + strlen(s2) + 1)))
		return (0);
	i = 0;
	while (*s1)
		ss[i++] = *s1++;
	while (*s2)
		ss[i++] = *s2++;
	ss[i] = '\0';
	return (ss);
}

void handler(t_struct *mini, char **env)
{
	pid_t pid = fork();
	// signal(SIGINT, proc_signal_handler);
		// ft_putchar('1');
	char *name = ft_strjoin("/bin/", mini->inp);
	char *arg[] = {name, NULL};
	if (pid == 0)
		execve(name, arg, env);
	else
		wait(&pid);
		
}


int main(int argc, char **argv, char **env)
{
	t_struct *mini;

	mini = malloc(sizeof(t_struct));
	char dir[PATH_MAX];
	getcwd(dir, sizeof(dir));
	while (1)
	{
		ft_putstr("\033[36m");
		ft_putstr("\033[45m");
		ft_putstr(dir);
		// ft_putstr("pishi zdes ->");
		ft_putstr("\033[0m");
		signal(SIGINT, signal_handler);
		vvod(mini);
		handler(mini, env);
	}
	

}