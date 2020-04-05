#include "../includes/ft_printf.h"

void	ft_printf_sec(char *format, t_struct *st, va_list ap) //19
{
	if (format[st->i] == 'd' || format[st->i] == 'i')
	{
		st->a = va_arg(ap, int);
		st->specif = 'd';
		specif_di(st, st->a, format);
	}
	else if (format[st->i] == 'o' || format[st->i] == 'u' || format[st->i] == 'x' || format[st->i] == 'X')
	{
		st->u = va_arg(ap, unsigned int);
		specif_uoxX(st, format, st->u);
		st->f_plus = 0;
	}
	if (format[st->i] == 'p')
	{
		st->d = va_arg(ap, long long int);
		hexadecimal(st->d, 0, st);
		st->schet = st->schet + re_putstr("0x");
		st->schet = st->schet + re_putstr(st->tmp);
		st->i++;
	}
}

int		ft_print_cs(int trig, t_struct *st, va_list ap) //25
{
	if (trig == 1)
	{
		st->s = va_arg(ap, char *);
		st->specif = 's';
		if (st->s == NULL)
			st->schet = st->schet + re_putstr("(null)");
		else
			st->tmp = st->s;
		st->i++;
	}
	else if (trig == 2)
	{
		st->c = va_arg(ap, int);
		if (!st->c )
		{
			st->c_trig = 1;
			st->tmp = "s";
		}
		else
		{
			st->tmp[0] = st->c;
			st->tmp[1] = '\0';
		}
		st->i++;
	}
	return 0;
}

void	specifier(char *format, t_struct *st, va_list ap) //18
{
	if (format[st->i] != 's' && format[st->i] != 'c' && format[st->i] != 'p' &&
		format[st->i] != 'd' && format[st->i] != 'i' &&
		format[st->i] != 'o' && format[st->i] != 'u' &&
		format[st->i] != 'x' && format[st->i] != 'X' && format[st->i] !=
		'f')
	{
		st->tmp[0] = format[st->i];
		st->tmp[1] = '\0';
		ft_print(format, st);
		st->i++;
		return ;
	}
	if (format[st->i] == 's')
		ft_print_cs(1, st, ap);
	else if (format[st->i] == 'c')
		ft_print_cs(2, st, ap);
	else
		ft_printf_sec(format, st, ap);
	ft_print(format, st);
}

void handle(char *format, va_list ap, t_struct *st)
{
	int i;
init(st);
			st->i++;
			flags(format, st, ap);
			width(format, st);
			// pres_check(format, st);
			i = length(format, st, ap);
			if (i == 0)
				specifier(format, st, ap);
			else
				ft_print(format, st);
}

int		ft_printf(char *format, ...)
{
	va_list		ap;
	t_struct	*st;

	st = (t_struct *)malloc(sizeof(t_struct));
	va_start(ap, format);
	st->i = 0;

	while (format[st->i] != '\0')
	{
		if (format[st->i] == '%')
			handle(format, ap, st);
		else if (format[st->i] == '{')
			proverka(format, st);
		else
		{
			st->schet = st->schet + re_putchar(format[st->i]);
			st->i++;
		}	
	}
	va_end(ap);
	return (st->schet);
}

// int main()
// {
// 	int i = ft_printf("@moulitest: %5.o %5.0o", 0, 0);
// 	printf("\ni = %d\n", i);
// 	printf("@moulitest: %5.o %5.0o", 0, 0);
//     return 0;
// }