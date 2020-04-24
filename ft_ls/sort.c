#include "ft_ls.h"

void	ft_sort(t_struct *st)
{
	int i;
	char *tmp;
	
	i = 0;
	st->trig = 0;
	tmp = (char *)ft_memalloc(sizeof(char *) * 10);
	while(i < st->j)
	{
		if (i+1 != st->j)
		{
			if (st->buf[i][0] >= 65 && st->buf[i][0] <= 90)
			{
				// printf("%d %s\n", i, st->buf[i]);
				ft_lower(st, i);
				st->trig = 1;
			}
			if (ft_strcmp(st->buf[i], st->buf[i + 1]) > 0)
			{
				tmp = st->buf[i];
				st->buf[i] = st->buf[i + 1];
				st->buf[i + 1] = tmp;
				i = 0;
				if (st->trig == 1)
					st->trig = 0;
			}
			else 
				i++;
		}
		else 
			i++;
	}
	int d = i;
	i = 0;
	if((st->l_fl + st->R_fl + st->r_fl + st->a_fl) == 0)
	{
		while(i < d)
		{
			printf("%s  ", st->buf[i]);
			i++;
		}
		printf("\n");
	}
}

void ft_lower(t_struct *st, int i)
{
	char a = st->buf[i][0];

	st->buf[i][0] = a + 32;
}

void to_upper(t_struct *st, int i)
{
	char a = st->buf[i][0];

	st->buf[i][0] = a - 32;
}

void				rev_sort(t_struct *st)
{
	int i = 0;
	st->trig = 0;
	char *tmp;
	tmp = (char *)ft_memalloc(sizeof(char *) * 10);
	while( i < st->schet)
	{
		if (i+1 != st->schet)
		{
			if (st->buf[i][0] >= 65 && st->buf[i][0] <= 90)
			{
				ft_lower(st, i);
				st->trig = 1;
			}
			if (ft_strcmp(st->buf[i], st->buf[i + 1]) < 0)
			{
				tmp = st->buf[i];
				st->buf[i] = st->buf[i + 1];
				st->buf[i + 1] = tmp;
				i = 0;
				if (st->trig == 1)
				{
				st->trig = 0;
				// break ;

				}
			}
			else 
				i++;
		}
		else 
			i++;
	}
	int d = i;
	i = 0;
	while(i < d)
	{
		printf("%s  ", st->buf[i]);
		i++;
	}printf("\n");
}

