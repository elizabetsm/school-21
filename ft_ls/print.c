#include "ft_ls.h"

void	open_dir(t_struct *st)
{
	st->buf = ft_memalloc(sizeof(char **) * 10);
	st->j = 0;
	int i = 0;

	if ((st->dir = opendir(st->dir_name)) == NULL)
	{
		perror("diropen");
   		exit(1);
	}
	else
	{	
		while ((st->entry = readdir(st->dir)) != NULL)
		{
			if (st->a_fl != 1 && st->entry->d_name[0] == '.')
				continue;
			st->buf[st->j] = st->entry->d_name;
			st->j++;
		}
		if (st->r_fl == 1)
			rev_sort(st);
		else
			ft_sort(st);
		if (st->l_fl == 1)
			l_param(st);
		st->i--;
	}
	closedir(st->dir);
}