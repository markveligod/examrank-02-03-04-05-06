#include <unistd.h>

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

int    check(char *str, char c, int index)
{
    int i;

    i = 0;
    while (i < index)
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}

int     main(int ac, char **av)
{
    int i;
    int j = 0;

    if (ac == 3)
    {
        i = 0;
        while (av[1][i])
        {
            if (check(av[1], av[1][i], i) == 0)
            {
                j = 0;
                while(av[2][j])
                {
                    if (av[2][j] == av[1][i])
                    {
                        ft_putchar(av[1][i]);
                        break;
                    }
                    j++;
                }
            }
            i++;
        }
    }
    ft_putchar('\n');
    return (0);
}
