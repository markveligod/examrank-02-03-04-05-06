#include <stdio.h>

int ft_printf(char *str, ...);

int main(void)
{
	int i = 1234456789;
	int j = -123456789;
	char *str = "Hell Old";
	printf("\n\nTEST %%s\n\n");
	printf("%d\n", ft_printf("%s : %20s : %2s : %.20s : %.2s : %20.2s : %20.20s : %2.20s : %20.11s\n", str, str, str, str, str, str, str, str, str));
	printf("%d\n", printf("%s : %20s : %2s : %.20s : %.2s : %20.2s : %20.20s : %2.20s : %20.11s\n", str, str, str, str, str, str, str, str, str));
	printf("\n\nTEST %%d\n\n");
	printf("%d\n", ft_printf("%d : %20d : %2d : %.20d : %.2d : %20.2d : %20.20d : %2.20d : %20.11d\n", j, j, j, j, j, j, j, j, j));
	printf("%d\n", printf("%d : %20d : %2d : %.20d : %.2d : %20.2d : %20.20d : %2.20d : %20.11d\n", j, j, j, j, j, j, j, j, j));
	printf("%d\n", ft_printf("%d : %20d : %2d : %.20d : %.2d : %20.2d : %20.20d : %2.20d : %20.11d\n", i, i, i, i, i, i, i, i, i));
	printf("%d\n", printf("%d : %20d : %2d : %.20d : %.2d : %20.2d : %20.20d : %2.20d : %20.11d\n", i, i, i, i, i, i, i, i, i));
	printf("\n\nTEST %%x\n\n");
	printf("%d\n", ft_printf("%x : %20x : %2x : %.20x : %.2x\n", j, j, j, j, j));
	printf("%d\n", printf("%x : %20x : %2x : %.20x : %.2x\n", j, j, j, j, j));
	printf("%d\n", ft_printf(" %20.20x : %2.20x : %20.11x : %20.2x\n", j, j, j, j));
	printf("%d\n", printf(" %20.20x : %2.20x : %20.11x : %20.2x\n", j, j, j, j));
	printf("%d\n", ft_printf("%x : %20x : %2x : %.20x : %.2x\n", i, i, i, i, i));
	printf("%d\n", printf("%x : %20x : %2x : %.20x : %.2x\n", i, i, i, i, i));
	printf("%d\n", ft_printf(" %20.20x : %2.20x : %20.11x : %20.2x\n", i, i, i, i));
	printf("%d\n", printf(" %20.20x : %2.20x : %20.11x : %20.2x\n", i, i, i, i));
	return (0);
}
