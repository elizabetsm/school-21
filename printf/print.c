
#include "../includes/ft_printf.h"
#include <unistd.h>
void	plus_print(t_struct *st)
{
	if (st->a >= 0)
		st->schet = st->schet + re_putchar('+');
	else if (st->a < 0 && st->f_nul == 1)
	{	
		free(st->tmp);
		st->a *= -1;
		st->tmp = itoa(st->a);
		st->schet = st->schet + re_putchar('-');
	}
	st->num_flags += 1;
}

void minus_print(char *format, t_struct *st)
{
	if (st->f_plus == 1)
		plus_print(st);
	if (st->f_pres == 1)
		pres_print(st);
	if (st->f_nul > 0 && st->f_minus != 1)
		null_print(st);
	if (st->f_resh == 1 && st->wdth_pres != -1)
	{
		if (st->nul == 0)
		{
			if (format[st->i] == 'x')
				st->schet = st->schet + re_putstr("0x");
			else if (format[st->i] == 'X')
				st->schet = st->schet + re_putstr("0X");
			else if (format[st->i] == 'o')
				st->schet = st->schet + re_putstr("0");
		}
	}
	if (st->f_pres == 0 || st->specif != 's')
		st->schet = st->schet + re_putstr(st->tmp);
	if (st->f_space == 1 || (st->wdht > 0 && st->f_nul != 1))
		space_print(st);
}

void print_else(char *format, t_struct *st)
{
	if (st->f_space == 1 || (st->wdht > 0 && st->f_nul != 1))
		space_print(st);
	if (st->f_plus == 1 )
		plus_print(st);
	if ((st->f_nul > 0 && st->f_minus != 1) && st->f_resh != 1)
		null_print(st);
	if (st->f_pres == 1)
		pres_print(st);
	if (st->f_resh == 1)
	{
		if (st->nul == 0 && st->tmp != "0")
		{
			if (format[st->i] == 'x')
				st->schet = st->schet + re_putstr("0x");
			else if (format[st->i] == 'X')
				st->schet = st->schet + re_putstr("0X");
			else if (format[st->i] == 'o')
				st->schet = st->schet + re_putstr("0");
		}
		if (st->f_nul > 0 && st->f_minus != 1)
			null_print(st);
	}
	if (st->c_trig == 1)
		st->schet = st->schet + re_putchar(st->c);
	else if (st->f_pres == 0 || st->specif != 's')
		st->schet = st->schet + re_putstr(st->tmp);
}

void	ft_print(char *format, t_struct *st)
{
	int i;

	i = 0;
	st->i = st->i - 1;
	if (st->tmp[0] == '%')
	{
		st->schet = st->schet + re_putchar(st->tmp[0]);
		st->i++;
		return ;
	}
	if (st->f_minus == 1)
		minus_print(format, st);
	else if (st->f_minus == 0)
		print_else(format, st);
	ft_free(st);
	st->i = st->i + 1;
}

void	space_print(t_struct *st)
{
	int d;

	int c = ft_strlen(st->tmp);
	if (st->wdht == 0 && st->f_space == 1)
		return ;
	if (st->f_pres == 1 && st->specif == 's')
		d = st->wdht - st->wdth_pres - st->f_plus;
	else if (st->f_pres == 1 && (st->wdth_pres < c) && st->specif != 's')
		d = st->wdht - c - st->f_plus;
	else if (st->f_pres == 1 && (st->wdth_pres >= c) && st->specif != 's')
		d = st->wdht - st->wdth_pres - st->f_plus;
	else
		d = st->wdht - c;
	if (st->f_resh == 1 && st->specif == 'x')
		d = d - 2;
	else if (st->f_resh == 1 && st->specif == 'o')
		d--;
	if ((st->a < 0) && st->f_pres == 1)
		d--;
	while (d-- > 0)
		st->schet = st->schet + re_putchar(' ');
}

void	null_print(t_struct *st)
{
	int d;
	
	d = st->wdht - ft_strlen(st->tmp) - st->num_flags - st->wdth_pres;
	if (st->f_resh == 1 && (st->specif == 'x' || st->specif == 'X'))
		d = d - 2;
	else if (st->f_resh == 1 && st->specif == 'o')
		d--;
	while (d-- > 0)
		st->schet = st->schet + re_putchar('0');
}