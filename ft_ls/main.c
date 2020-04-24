#include "ft_ls.h"

void	init(t_struct *st)
{
	st->trig = 0;
	st->l_fl = 0;
	st->r_fl = 0;
	st->a_fl = 0;
	st->t_fl = 0;
	st->R_fl = 0;
	st->dir_name = ft_memalloc(5);
	ft_strcpy(st->dir_name, ".");
}

void	parse(int argc, char **argv)
{
	t_struct *st;
	st = (t_struct *)ft_memalloc(sizeof(t_struct));
	init(st);
	st->argc = argc;
	// st->dir_name = ft_memalloc(sizeof(char) * 20);
	// st->dir_name = ".";
	if (argc == 1)
		open_dir(st);
	st->i = 1;
	st->j = 0;
	while (st->i < argc)
	{
		if (argv[st->i][0] == '-')
			find_opt(st, argv);
		else if (argv[st->i][0] >=65 && argv[st->i][0] <= 122)
			find_dir(st, argv);
		st->i++;
	}

}

void	find_dir(t_struct *st, char **argv)
{
	int i = 0;
	int d = ft_strlen(argv[st->i]);
	st->dir_name = (char *)ft_memalloc( 4 * d);
	while(i < d)
	{
		st->dir_name[i] = argv[st->i][i];
		i++;
	}
	st->i++;
	if ((st->i < st->argc) && (argv[st->i][0] == '-'))
		find_opt(st, argv);
	else
		open_dir(st);
}

void	find_opt(t_struct *st, char **argv)
{
	int i = 0;
	while (argv[st->i][i] != '\0')
	{
		if (argv[st->i][i] == 'a')
			st->a_fl = 1;
		if (argv[st->i][i] == 'r')
			st->r_fl = 1;
		if (argv[st->i][i] == 'R')
			st->R_fl = 1;
		if (argv[st->i][i] == 'l')
			st->l_fl = 1;
		if (argv[st->i][i] == 't')
			st->t_fl = 1;
		i++;
	}
	st->i++;
	if ((st->i < st->argc) && (argv[st->i][0] >=65 && argv[st->i][0] <= 122))
		find_dir(st, argv);
	else
		open_dir(st);

}

int	main(int argc, char ** argv)
{
	// int i = 0;
	// while (i < argc)
	// {
	// 	printf("argv[%d] -> %s\n argc == %d\n", i, argv[i], argc);
	// 	i++;
	// }
	// printf("/%s/", argv[1]);
	parse(argc, argv);
	return (0);
}