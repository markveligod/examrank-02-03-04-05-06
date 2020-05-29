#include <stdio.h>

int ft_printf(char const *format, ...);

int 	main(void)
{
    int res_1;
    int res_2;

//STR   
    res_2 = printf("%10.2s\n", "toto");
    res_1 = ft_printf("%10.2s\n", "toto");
    if (res_1 != res_2)
        printf("===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_2 = printf("%2.2s\n", "toto");
    res_1 = ft_printf("%2.2s\n", "toto");
    if (res_1 != res_2)
        printf("===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_2 = printf("%2.20s\n", "toto");
    res_1 = ft_printf("%2.20s\n", "toto");
    if (res_1 != res_2)
        printf("===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_2 = printf("%20.20s\n", "toto");
    res_1 = ft_printf("%20.20s\n", "toto");
    if (res_1 != res_2)
        printf("===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);


    res_2 = printf("%.2s\n", "toto");
    res_1 = ft_printf("%.2s\n", "toto");
    if (res_1 != res_2)
        printf("===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_2 = printf("%.20s\n", "toto");
    res_1 = ft_printf("%.20s\n", "toto");
    if (res_1 != res_2)
        printf("===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);


    res_2 = printf("%12s\n", "toto");
    res_1 = ft_printf("%12s\n", "toto");
    if (res_1 != res_2)
        printf("===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_2 = printf("%2s\n", "toto");
    res_1 = ft_printf("%2s\n", "toto");
    if (res_1 != res_2)
        printf("===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);


    res_2 = printf("%s\n", "toto");
    res_1 = ft_printf("%s\n", "toto");
    if (res_1 != res_2)
        printf("===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

//INT
    res_1 = ft_printf("Magic %s is %15d\n", "number", 42);
    res_2 = printf("Magic %s is %15d\n", "number", 42);
    if (res_1 != res_2)
        printf("1)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_1 = ft_printf("Magic %s is %1d\n", "number", 42);
    res_2 = printf("Magic %s is %1d\n", "number", 42);
    if (res_1 != res_2)
        printf("2)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);


    res_1 = ft_printf("Magic %s is %15.2d\n", "number", 42);
    res_2 = printf("Magic %s is %15.2d\n", "number", 42);
    if (res_1 != res_2)
        printf("3)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_1 = ft_printf("Magic %s is %15.20d\n", "number", 42);
    res_2 = printf("Magic %s is %15.20d\n", "number", 42);
    if (res_1 != res_2)
        printf("4)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);


    res_1 = ft_printf("Magic %s is %.20d\n", "number", 42);
    res_2 = printf("Magic %s is %.20d\n", "number", 42);
    if (res_1 != res_2)
        printf("5)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_1 = ft_printf("Magic %s is %.2d\n", "number", 42);
    res_2 = printf("Magic %s is %.2d\n", "number", 42);
    if (res_1 != res_2)
        printf("6)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_1 = ft_printf("Magic %s is %d\n", "number", 42);
    res_2 = printf("Magic %s is %d\n", "number", 42);
    if (res_1 != res_2)
        printf("7)===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

// HEX
    res_1 = ft_printf("Hexadecimal for %d is %x\n", 42, 42);
    res_2 = printf("Hexadecimal for %d is %x\n", 42, 42);
    if (res_1 != res_2)
        printf("===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_1 = ft_printf("Hexadecimal for %d is %20x\n", 42, 42);
    res_2 = printf("Hexadecimal for %d is %20x\n", 42, 42);
    if (res_1 != res_2)
        printf("===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_1 = ft_printf("Hexadecimal for %d is %1x\n", 42, 42);
    res_2 = printf("Hexadecimal for %d is %1x\n", 42, 42);
    if (res_1 != res_2)
        printf("===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_1 = ft_printf("Hexadecimal for %d is %1.1x\n", 42, 42);
    res_2 = printf("Hexadecimal for %d is %1.1x\n", 42, 42);
    if (res_1 != res_2)
        printf("===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

    res_1 = ft_printf("Hexadecimal for %d is %10.1x\n", 42, 42);
    res_2 = printf("Hexadecimal for %d is %10.1x\n", 42, 42);
    if (res_1 != res_2)
        printf("===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);
    
     res_1 = ft_printf("Hexadecimal for %d is %.1x\n", 42, 42);
    res_2 = printf("Hexadecimal for %d is %.1x\n", 42, 42);
    if (res_1 != res_2)
        printf("===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

      res_1 = ft_printf("Hexadecimal for %d is %.10x\n", 42, 42);
    res_2 = printf("Hexadecimal for %d is %.10x\n", 42, 42);
    if (res_1 != res_2)
        printf("===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);

       res_1 = ft_printf("Hexadecimal for %d is %10.10x\n", 42, 42);
    res_2 = printf("Hexadecimal for %d is %10.10x\n", 42, 42);
    if (res_1 != res_2)
        printf("===============ERROR===============\n\nprintf: %d\nft_printf: %d\n\n", res_2, res_1);
}