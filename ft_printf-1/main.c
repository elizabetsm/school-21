#include "includes/ft_printf.h"

int main()
{
    ft_printf("%.*s", -3, 0);
    printf("%.*s", -3, 0);
    return 0;
}