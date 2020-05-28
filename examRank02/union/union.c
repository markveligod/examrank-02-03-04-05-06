#include <unistd.h>

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

int     main(int ac, char **av)
{
    int i;
    int j;

    if (ac == 3)
    {
        i = 0;
        while(av[1][i])
        {
            j = 0;
            while (j < i)
            {
                if (av[1][i] == av[1][j])
                    break;
                j++;
            }
            if (i == j)
                ft_putchar(av[1][i]);
            i++;
        }
        i = 0;
        while(av[2][i])
        {
            j = 0;
            while(av[1][j])
            {
                if (av[1][j] == av[2][i])
                    break;
                j++;
            }
            if (av[1][j] != '\0')
            {
                i++;
                continue;
            }
            j = 0;
            while (j < i)
            {
                if (av[2][i] == av[2][j])
                    break;
                j++;
            }
            if (i == j)
                ft_putchar(av[2][i]);
            i++;
        }
    }
    ft_putchar('\n');
    return (0);
}