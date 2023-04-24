#include "../ft_printf.h"

int s_specifier(char *str)
{
    int index;

    index = 0;
    if (!str)
    {
		write(1, (const void *)"(null)", 6);
		return (6);
    }
    while (str[index])
    {
        write(1, &str[index], 1);
        index++;
    }
    return (index);
}