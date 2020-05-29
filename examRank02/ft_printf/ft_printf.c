#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_lst
{
    int width;
    int point;
    int precision;
} t_lst;

t_lst   ft_init_flags(t_lst list_flags)
{
    list_flags.width = 0;
    list_flags.point = 0;
    list_flags.precision = 0;
    return (list_flags);
}

int		ft_check_flag(char flag)
{
	return ((flag >= '0' && flag <= '9') || flag == '.');
}

t_lst   ft_cut_flags(const char *flag, t_lst list_flags)
{
    int i;

    i = 0;
    while (flag[i] && ft_check_flag(flag[i]))
    {
        if ((flag[i] >= '0' && flag[i] <= '9') && list_flags.point == 0)
            list_flags.width = (list_flags.width * 10) + (flag[i] - '0');
        else if (flag[i] == '.')
            list_flags.point = 1;
        else if ((flag[i] >= '0' && flag[i] <= '9') && list_flags.point == 1)
            list_flags.precision = (list_flags.precision * 10) + (flag[i] - '0');
        i++;
    }
    return (list_flags);
}

int     ft_strlen(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

int     check_size(int n)
{
	int		count;
	long	res;

	res = n;
	count = 1;
	if (res < 0)
	{
		count++;
		res *= (-1);
	}
	while (res >= 10)
	{
		count++;
		res /= 10;
	}
	return (count);
}

char    *ft_itoa(int n)
{
	char	*array;
	long	res;
	int		i;

	i = 0;
	if (!(array = (char*)malloc(sizeof(char) * check_size(n) + 1)))
		return (NULL);
	if (n < 0)
		array[0] = '-';
	res = n;
	if (res < 0)
		res *= (-1);
	array[check_size(n) - i++] = '\0';
	while (res >= 10)
	{
		array[check_size(n) - i++] = (res % 10) + '0';
		res /= 10;
	}
	array[check_size(n) - i++] = (res % 10) + '0';
	return (array);
}

int     ft_add_width(int size, char c)
{
    int i;

    i = 0;
    while (i < size)
    {
        write(1, &c, 1);
        i++;
    }
    return (i);
}

int     ft_putstr(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
    return (i);
}

int     ft_print_int(t_lst list_flags, va_list argv)
{
    int count;
    int num;
    char *str;
    int size;

    count = 0;
    num = va_arg(argv, int);
    str = ft_itoa(num);
    size = ft_strlen(str);
    if (list_flags.width > size)
        count += ft_add_width((list_flags.precision > size) ? list_flags.precision - size : list_flags.width - size, (list_flags.precision > size) ? '0' : ' ');
    else
        count += (list_flags.precision > size) ? ft_add_width(list_flags.precision - size, '0') : 0;
    count += ft_putstr(str);
    free(str);
    return (count);
}

char     *ft_strdup(char *str)
{
    char *array;
    int i;
    int size;

	i = 0;
    size = ft_strlen(str);
    if(!(array = (char *)malloc(sizeof(char) * (size + 1))))
        return (NULL);
    while (str[i])
    {
        array[i] = str[i];
        i++;
    }
    array[i] = '\0';
    return (array);
}

int     ft_print_str(t_lst list_flags, va_list argv)
{
    char	*str;
	int		size;
	int		count;
    int     i;

    count = 0;
	if (!(str = va_arg(argv, char *)))
		str = ft_strdup("(null)");
	size = ft_strlen(str);
    if (list_flags.width > size)
        count += ft_add_width(list_flags.width - ((list_flags.precision > 0 && list_flags.precision < size) ? list_flags.precision : size), ' ');
    if (list_flags.precision > 0 && list_flags.precision < size)
    {
        i = 0;
        while (i < list_flags.precision)
        {
            write(1, &str[i], 1);
            count++;
            i++;
        }
    }
    else
        count += ft_putstr(str);
    return (count);
}

int		ft_check_num(unsigned long long number, int size)
{
	int	count;

	count = 0;
	while (number > 0)
	{
		number /= size;
		count++;
	}
	return (count);
}

char	*ft_convert_pointer(char *array_hex, unsigned long long number)
{
	int		size_hex;
	int		count_num;
	char	*str;

	size_hex = ft_strlen(array_hex);
	count_num = ft_check_num(number, size_hex);
	if (!(str = (char *)malloc(sizeof(char) * (count_num + 1))))
		return (NULL);
	str[count_num] = '\0';
	while (--count_num)
	{
		str[count_num] = array_hex[number % size_hex];
		number /= size_hex;
	}
	if (count_num == 0)
		str[count_num] = array_hex[number % size_hex];
	return (str);
}

int     ft_print_xxx(char *array_hex, t_lst list_flags, va_list argv)
{
    char				*str;
	int					size;
	int					count;
	unsigned long long	num;

	num = va_arg(argv, unsigned long long);
	if (!num)
		str = ft_strdup("0");
	else
		str = ft_convert_pointer(array_hex, num);
	size = ft_strlen(str);
	count = 0;
    if (list_flags.width > 0)
        count += (list_flags.precision > size) ? ft_add_width(list_flags.precision - size, '0') : ft_add_width(list_flags.width - size, ' ');
    else
        count += (list_flags.precision > size) ? ft_add_width(list_flags.precision - size, '0') : 0;
    count += ft_putstr(str);
    free(str);
    return (count);
}

int     ft_print_value(char flag, t_lst list_flags, va_list argv)
{
    int count;

    count = 0;
    if (flag == 'd')
        count += ft_print_int(list_flags, argv);
    else if (flag == 's')
        count += ft_print_str(list_flags, argv);
    else if (flag == 'x')
        count += ft_print_xxx("0123456789abcdef", list_flags, argv);
    return (count);
}

int     ft_printf(const char *str, ... )
{
    int count;
    int i;
    va_list argv;
    t_lst list_flags;

    count = 0;
    i = 0;
    va_start(argv, str);
    while (str[i])
    {
        count += (str[i] == '%') ? 0 : 1;
        if (str[i] == '%')
        {
            i++;
            list_flags = ft_init_flags(list_flags);
            list_flags = ft_cut_flags(&str[i], list_flags);
            while (ft_check_flag(str[i]))
                i++;
            count += ft_print_value(str[i], list_flags, argv);
        }
        else
            write(1, &str[i], 1);
        i++;
    }
    va_end(argv);
    return (count);
}
