#include "../ft_printf.h"

int c_specifier(char c)
{
    write(1, &c, 1);
    return (1);
}