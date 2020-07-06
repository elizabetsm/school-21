#include "../includes/ft_printf.h"
# define SIZE_E 127
# define SIZE_M 23

//void    bit_parcer(long double f)
//{
//    t_sun eeei;
//    //unsigned displayMask = 1 << 22;
//    int c;
//
//    eeei.f = f;
//    printf("\n");
////    printf("%d_ %d_ %d  %f\n", eeei.v.sign, eeei.v.exp, eeei.v.mant, eeei.f);
//    for (c=0; c<=23; c++)
//    {
//        ft_putchar(eeei.v.mant & (1 << c) ? '1' : '0');
//        //eeei.v.mant <<= 1;
//
////        if (c % 8 == 0)
////            putchar(' ');
//    }
//}

void    *ft_cpy(char *newptr, char *ptr, int size)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (ptr[i] != '\0')
    {
        newptr[i] = ptr[i];
        i++;
    }
    while (i < size)
    {
        newptr[i] = '0';
        i++;
    }
    return (newptr);
}

void	*ft_realloc(void *ptr, size_t size)
{
    char	*newptr;

//    if (size == 64)
//        printf("1\n");
//    printf("realloc\n");
    if (!size && ptr)
    {
        if (!(newptr = (char *)malloc(1)))
            return (NULL);
        ft_memdel(&ptr);
        return (newptr);
    }
    if (!(newptr = (char *)malloc(size)))
        return (NULL);
    if (ptr)
    {
        ft_cpy(newptr, ptr, size);
        //free(ptr);
        //ft_memdel(&ptr);
    }
//    printf("newptr:%s\n", newptr);
    return (newptr);
}

int two_degree(int s)
{
    int i;
    unsigned long long a;

    a = 1;
    i = 0;
    while (i < s)
    {
        a *= 2;
        i++;
    }
    return (a);
}

void    *get_char(char *arr)
{
    char *mas;
    int i;
    int j;
    char tmp;

    j = ft_strlen(arr);
    i = 0;
    mas = ft_memalloc(ft_strlen(arr));
    while (arr[i] != '\0')
    {
        mas[i] = arr[j - 1];
        i++;
        j--;
    }
//    ft_memdel(&arr);
    return (mas);
}

void    *sum_char(char *ans, char *tmp)
{
    int i;
    int j;
    char symb;
    char *str;
    char *newptr;

    str = ft_memalloc(ft_strlen(tmp));
    ft_strcpy(str, tmp);
    i = ft_strlen(ans);
    j = ft_strlen(str);
    while ((i - 1) == j || j > i)
    {
        ans = ft_realloc(ans, (i*2));
        i = ft_strlen(ans);
        j = ft_strlen(str);
    }

    i = 0;
    while (str[i] != '\0' && ans[i] != '\0')
    {
        symb = str[i];
        ans[i] += symb - '0';
        if (ans[i] > '9')
        {
            if (ans[i + 1] == '\0')
            {
                newptr = ft_strnew(j + 1);
                ft_strcpy(newptr, ans);
                newptr[i] -= 10;
                newptr[i + 1] = 49;
                free(ans);
                return (newptr);
            }
            else
            {
                ans[i + 1]++;
                ans[i] -= 10;
            }
        }
        i++;
    }
    return (ans);
}

void    *sum_reverse(char *ans, char *tmp)
{
    int i;
    int j;
    int k;
    char symb;
    char *arr;

    i = ft_strlen(ans);
    j = ft_strlen(tmp);
    arr = ft_memalloc(j);
    arr = get_char(tmp);
    while ((i - 1) == j || j > i)
    {
        ans = ft_realloc(ans, (i*2));
        i = ft_strlen(ans);
    }
//    while (i > j && ans[i - 1] == '0')
//        i--;
    i = 0;
    j = 0;
    while (arr[j] != '\0')
    {
        symb = arr[j];
        ans[i] += symb - '0';
        k = i;
        while (k > 0)
        {
            if (ans[k] > '9')
            {
                ans[k - 1]++;
                ans[k] -= 10;
            }
            k--;
        }
        i++;
        j++;
    }
    return (ans);
}

void    *get_zero(char *arr)
{
    char *newptr;
    int i;

    newptr = ft_memalloc(ft_strlen(arr) + 2);
    i = 0;
    while (arr[i] != '\0')
    {
        newptr[i] = arr[i];
        i++;
    }
    newptr[i] = '0';
    newptr[i + 1] = '\0';
    ft_memdel(&arr);
    return (newptr);
}

void    *multiplication(char *arr, int num, int deg)
{
    int i;
    int j;
    char symb;
    char *newptr;

    i = ft_strlen(arr);
    newptr = ft_memalloc(ft_strlen(arr) + 1);
    ft_strcpy(newptr, arr);

    i = 0;
    while (i < num - 1)
    {
        j = 0;
        while (arr[j] != '\0')
        {
            symb = arr[j];
            newptr[j] += symb - '0';
            if (newptr[j] > '9')
            {
                if (newptr[j + 1] == '\0')
                    newptr[j + 1] = '0';
                newptr[j + 1]++;
                newptr[j] -= 10;
            }
            j++;
        }
        i++;
    }
    i = ft_strlen(newptr);
    if (ft_strlen(newptr) < deg)
        newptr = get_zero(newptr);
//    printf("newptr:%s\n", newptr);
    return (newptr);
}

int exp_shift(t_sun eeei)
{
    int a;

    a = eeei.v.exp - SIZE_E;
    return (a);
}

int     check_zero_inf(t_sun eeei, t_struct *st)
{
    int round;
    int i;

    i = 0;
    if (st->f_pres == 1)        //надо записать round в структуру
        round = st->wdth_pres;  //и удалить такую же операцию  в roundation
    else
        round = 6;
    if (eeei.v.exp == 0 && eeei.v.mant == 0)
    {
        ft_putchar('0');
        ft_putchar('.');
        while (i < round)
        {
            ft_putchar('0');
            i++;
        }
        return (1);
    }

    if (eeei.v.exp == 255)
    {
        ft_putstr("inf");
        return (1);
    }
    return (0);
}

void    after_point(t_sun eeei, t_struct *st)
{
//    char *sp;
//    int size;
    char *arr;
    int count;
    int c;
    int b;

//    size = 8;
    arr = ft_memalloc(2);
//    sp = ft_memalloc(size);
//    sp = ft_realloc(sp, size);
    arr[0] = '1';
//    printf("sp:%s\n", sp);
    count = 0;
    for (c = (SIZE_M - st->shift - 1); c >= 0; c--)
    {
        count++;
        eeei.v.mant & (1 << c) ? (b = 1) : (b = 0);
        arr = multiplication(arr, 5, count);
        if (b == 1)
        {
            st->sp = sum_reverse(st->sp, arr);
//            printf("sp:%s arr:%s c:%d %d %d\n", sp, arr, c, ft_strlen(sp), ft_strlen(arr));
        }
    }
}

void    bit_parcer(float f, t_struct *st)
{
    t_sun eeei;
    int c;
    int b;
    int count;
    unsigned long long sum;
    char *arr;


    st->f = 1;
    st->size = 8;
    eeei.f = f;
//    if (eeei.v.sign == 1)
//        ft_putchar('-');
    c = check_zero_inf(eeei, st);
    if (c == 1)
        return;
    st->sp = ft_memalloc(st->size);
    st->sp = ft_realloc(st->sp, st->size);
    st->fp = ft_memalloc(st->size);
    st->fp = ft_realloc(st->fp, st->size);
    arr = ft_memalloc(1);
    arr[0] = '1';
    sum = 0;
    st->shift = exp_shift(eeei);
    for (c = (SIZE_M - st->shift); c < SIZE_M; c++)
    {
        if (c == (SIZE_M - st->shift))
        {
            eeei.v.mant & (1 << c) ? (b = 1) : (b = 0);
            if (b == 1)
                st->fp = sum_char(st->fp, arr);
            continue ;
        }
        if (c < 0)
        {
            arr = sum_char(arr, arr);
            continue ;
        }
        eeei.v.mant & (1 << c) ? (b = 1) : (b = 0);
        arr = sum_char(arr, arr);
        if (b == 1)
            st->fp = sum_char(st->fp, arr);
    }
    if (st->shift != 0)
        arr = sum_char(arr, arr);
    st->fp = sum_char(st->fp, arr);
    st->fp = get_char(st->fp);
    ft_memdel(&arr);
    after_point(eeei, st);
    print_float(st->fp, st->sp, st, t_sun eeei);

}
