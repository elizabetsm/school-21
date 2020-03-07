#include "../includes/ft_printf.h"

int    length(char *format, t_struct *st, va_list ap) //основная функция
// обработки флагов
{
    if (format[st->i] == 'h' && format[st->i + 1] == 'h')
    {
        st->i = st->i + 2;
        if (format[st->i] == 'd' || format[st->i] == 'i')
        {
            st->a = (char)va_arg(ap, int);
            specif_di(st, st->a, format);
        }
        else if (format[st->i] == 'o' || format[st->i] == 'u' || format[st->i] == 'x' || format[st->i] == 'X')
        {
            st->a = (unsigned char)va_arg(ap, int);
            specif_uoxX(st, format, st->a);
        }
    }
    else if (format[st->i] == 'h')
    {
        st->i++;
        if (format[st->i] == 'd' || format[st->i] == 'i')
        {
            st->a = (short int)va_arg(ap, int);
            specif_di(st, st->a, format);
        }
        else if (format[st->i] == 'o' || format[st->i] == 'u' || format[st->i] == 'x' || format[st->i] == 'X')
        {
            st->a = (unsigned short int)va_arg(ap, int);
            specif_uoxX(st, format, st->a);
        }
    }
    else if (format[st->i] == 'l' || (format[st->i] == 'l' && format[st->i + 1] == 'l'))
    {
        st->i++;
        if (format[st->i] == 'l')
            st->i++;
        if (format[st->i] == 'd' || format[st->i] == 'i')
        {
            st->d = va_arg(ap, long long int);
            specif_di(st, st->d, format);
        }
        else if (format[st->i] == 'o' || format[st->i] == 'u' || format[st->i] == 'x' || format[st->i] == 'X')
        {
            st->o = va_arg(ap, unsigned long long int);
            specif_uoxX(st, format, st->o);
        }
    }
    else
		return (0);
	return (1);
}

void    specif_di(t_struct *st, long long int a, char *format) //для сапецификатора d, i
{
    st->tmp = itoa(a);
	// ft_print(format, st);
    st->i++;
}

void    specif_uoxX(t_struct *st, char *format, unsigned long long int a) //для спецификаторов u, o, xX(не работает 16ричная отрицательная)
{
	int trig;

	trig = 0;
    if (format[st->i] == 'o')
	{
    	st->specif = 'o';
		octal(a, st);
		st->i++;
	}
    else if (format[st->i] == 'x' || format[st->i] == 'X')
    {
    	st->specif = 'x';
		if (format[st->i] == 'X')
			trig = 1;
		hexadecimal(a, trig, st);
		st->i++;
	}
	else if (format[st->i] == 'u')
	{
		st->tmp = itoa(a);
		st->i++;
	}
}

int		hexadecimal(long long int a, int trig, t_struct *st) //%X  33+ stroki
{
	int	i;
	int	f;
	
	f = 0;
	if (a == 0)
	{
		st->tmp = ft_memalloc(5);
		st->tmp[0] = '0';
		//ft_putchar('0');
		return 0;
	}
	st->l = ft_memalloc(2);
	st->str = ft_memalloc(100);
	while (a > 0)
	{
		i = a % 16;
		if (i <= 9)
		{
			st->tmp = ft_strjoin(st->str, itoa(i));
			free(st->str);
			st->str = st->tmp;
		}
		else
		{
			if (trig == 1)
				st->l[0] = (i - 10) + 'A';
			else
				st->l[0] = (i - 10) + 'a';
			st->l[1] = '\0';
			st->tmp = ft_strjoin(st->str, st->l);
			free(st->str);
			st->str = st->tmp;
		}
		a = a/16;
		f++;
	}
	st->tmp = ft_memalloc(40);
	a = 0;
	while(--f >= 0)
		st->tmp[a++] = st->str[f];
	st->tmp[a] = '\0';
	return (0);
}

int		octal(unsigned long long int a, t_struct *st)
{
	int	i;
	int	f;
	
	f = 0;
	if (a == 0)
	{
		ft_putchar('0');
		return 0;
	}
	st->str = ft_memalloc(100);
	while (a > 0)
	{
		i = a % 8;
		st->tmp = ft_strjoin(st->str, itoa(i));
		free(st->str);
		st->str = st->tmp;
		a = a/8;
		f++;
	}
	st->tmp = ft_memalloc(40);
	a = 0;
	while(--f >= 0)
		st->tmp[a++] = st->str[f];
	st->tmp[a] = '\0';
	return (0);
}
