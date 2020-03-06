/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efleta <efleta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 19:09:51 by efleta            #+#    #+#             */
/*   Updated: 2020/03/02 15:15:58 by efleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_length(long long int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		n = n * (-1);
		i++;
	}
	while ((n / 10) > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*itoa(long long int n)
{
	char			*a;
	int				len;
	long long int	tmp;
	
//    if (n == -9223372036854775808)
//        return (ft_strdup("-9223372036854775808"));
	len = ft_length(n);
	tmp = n;
	if (!(a = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	if (n == 0)
		a[0] = '0';
	if (n < 0)
	{
		a[0] = '-';
		n = n * (-1);
	}
	a[len] = '\0';
	while (n > 0)
	{
		len--;
		a[len] = (n % 10) + '0';
		n = n / 10;
	}
	return (a);
}

void	ft_printf_sec(char *format, t_struct *st, va_list ap)
{
	
	if (format[st->i] == 'd' || format[st->i] == 'i')
	{
		st->a = va_arg(ap, int);
		specif_di(st, st->a, format);
	}
	else if (format[st->i] == 'o' || format[st->i] == 'u' || format[st->i] == 'x' || format[st->i] == 'X')
	{
		unsigned int d;
		d = va_arg(ap, unsigned int);
		specif_uoxX(st, format, d);
	}
	if (format[st->i] == 'p')
	{
		st->d = va_arg(ap, long long int);
		hexadecimal(st->d, 0, st);
		st->schet = st->schet + re_putstr("0x");
		st->schet = st->schet + re_putstr(st->tmp);
		st->i++;
	}
	ft_print(format, st);
}

int		ft_print_cs(int trig, t_struct *st, va_list ap)
{
	if (trig == 1)
	{
		st->s = va_arg(ap, char *);
		st->schet = st->schet + re_putstr(st->s);
		st->i++;
	}
	else if (trig == 2)
	{
		st->c = va_arg(ap, int);
		st->schet = st->schet + re_putchar(st->c);
		st->i++;
	}
	return 0;
}

int		ft_printf(char *format, ...) //сюда нужно вставить остальные флаги и ширину
{
	va_list		ap;
	t_struct	*st;

	st = (t_struct *)malloc(sizeof(t_struct));
	va_start(ap, format);
	st->i = 0;
	while (format[st->i] != '\0')
	{
		if (format[st->i] == '%')
		{
			st->i++;
			if (format[st->i] == '%')
			{
				ft_putchar('%');
				st->i++;
			}
			flags(format, st, ap);
			width(format, st);
			length(format, st, ap);
			if (format[st->i] == 's')
				ft_print_cs(1, st, ap);
			if (format[st->i] == 'c')
				ft_print_cs(2, st, ap);
			else
				ft_printf_sec(format, st, ap);
		}
		else
		{
			st->schet = st->schet + re_putchar(format[st->i]);
			st->i++;
		}	
	}
	va_end(ap);
	return (st->schet);
}

int main()
{
    // int *b;
    // int a = 0x10d;
    // b = &a;
    int a = printf("%x\n", 4294967296);
	printf("a = %d\n", a);
	int i = ft_printf("%x\n", 4294967296);
	printf("i = %d\n", i);
    return 0;
}