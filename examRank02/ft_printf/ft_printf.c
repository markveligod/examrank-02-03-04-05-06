#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_list
{
	int width;
	int point;
	int precis;
} t_list;

t_list init_struct(t_list flags)
{
	flags.width = 0;
	flags.point = 0;
	flags.precis = 0;
	return (flags);
}

int ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int is_spec(char c)
{
	return (c == 's' || c == 'd' || c == 'x');
}

t_list pars_flags(t_list flags, char *str)
{
	int i = 0;

	while (str[i] && (is_spec(str[i]) == 0))
	{
		if (ft_isdigit(str[i]) && flags.point == 0)
			flags.width = (flags.width * 10) + (str[i] - '0');
		else if (str[i] == '.' && flags.point == 0)
			flags.point = 1;
		else if (ft_isdigit(str[i]) && flags.point == 1)
			flags.precis = (flags.precis * 10) + (str[i] - '0');
		i++;
	}
	return (flags);
}

int check_size(int number)
{
	unsigned int num;
	int count = 0;

	if (number == 0)
		return (1);
	if (number < 0)
	{
		count++;
		num = number * (-1);
	}
	else
		num = number;
	while (num > 0)
	{
		count++;
		num /= 10;
	}
	return (count);
}

int ft_strlen (char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return (i);
}

char *get_num(int number, int size)
{
	unsigned num;
	char *str;

	str = (char *)malloc(sizeof(char) * (size + 1));
	str[size] = '\0';
	if (number == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (number < 0)
		num = number * (-1);
	else
		num = number;
	while (--size > 0)
	{
		str[size] = (num % 10) + '0';
		num /= 10;
	}
	if (number < 0)
		str[size] = '-';
	else
		str[size] = (num % 10) + '0';
	return (str);
}

int print_width(int size, char c)
{
	int count = 0;

	while (count < size)
	{
		write(1, &c, 1);
		count++;
	}
	return (count);
}

int ft_putstr(char *str, int size)
{
 	    int count = 0;
 
 	    while (count < size)
	    {
	        write(1, &str[count], 1);
	        count++;
	    }
	 return (count);
}

int print_int(t_list flags, va_list value)
{
	int count = 0;
	int number;
	char *str;
	int size;

	number = va_arg(value, int);
	size = check_size(number);
	str = get_num(number, size);
	if (flags.precis == 0 && flags.point == 1 && number == 0)
	{
		free(str);
		str = "";
	}
	size = ft_strlen(str);
	if (number < 0)
		size--;
	count += print_width(flags.width - ((flags.precis > size ? ((number < 0) ? (flags.precis + 1) : flags.precis) : ((number < 0) ? (size + 1) : size))), ' ');
	if (number < 0)
		count += print_width(1, '-');
	count += print_width(flags.precis - size, '0');
	count += ft_putstr(((number < 0) ? &str[1] : &str[0]), size);
	if (!(flags.precis == 0 && flags.point == 1 && number == 0))
		free(str);
	return (count);
}

int print_str(t_list flags, va_list value)
{
	char *str;
	int size;
	int count = 0;

	str = va_arg(value, char *);
	if (!str)
		str = "(null)";
	if (flags.precis == 0 && flags.point == 1)
		str = "";
	size = ft_strlen(str);
	count += print_width(flags.width - ((flags.precis > 0 && flags.precis < size) ? flags.precis : size), ' ');
	count += ft_putstr(str, ((flags.precis > 0 && flags.precis < size) ? flags.precis : size));
	return (count);
}

int check_long(unsigned long long number)
{
	int count = 0;

	while (number > 0)
	{
		count++;
		number /= 16;
	}
	return (count);
}

char *get_long(unsigned int number)
{
	char *str;
	int size;
	char *array_hex = "0123456789abcdef";

	size = check_long(number);
	str = (char *)malloc(sizeof(char) * (size + 1));
	str[size] = '\0';
	if (number == 0)
	{
		str[0] = '0';
		return (str);
	}
	while (--size > 0)
	{
		str[size] = array_hex[number % 16];
		number /= 16;
	}
	if (size == 0)
		str[size] = array_hex[number % 16];
	return (str);
}

int print_xxx(t_list flags, va_list value)
{
	int count = 0;
	int size;
	char *str;
	unsigned int number;

	number = va_arg(value, unsigned int);
	str = get_long(number);
	if (flags.precis == 0 && flags.point == 1 && number == 0)
	{
		free(str);
		str = "";
	}
	size = ft_strlen(str);
	count += print_width(flags.width - ((flags.precis > size) ? flags.precis : size), ' ');
	count += print_width(flags.precis - size, '0');
	count += ft_putstr(str, size);
	if (!(flags.precis == 0 && flags.point == 1 && number == 0))
		free(str);
	return (count);
}

int 	sort_spec(char c, t_list flags, va_list value)
{
	int count = 0;

	if (c == 'd')
		count += print_int(flags, value);
	if (c == 's')
		count += print_str(flags, value);
	if (c == 'x')
		count += print_xxx(flags, value);
	return (count);
}

int ft_printf(char *str, ...)
{
	int count = 0;
	va_list value;
	int i = 0;
	t_list flags;

	va_start(value, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			flags = init_struct(flags);
			flags = pars_flags(flags, &str[i]);
			while (is_spec(str[i]) == 0)
				i++;
			count += sort_spec(str[i], flags, value);
		}
		else
		{
			write(1, &str[i], 1);
			count++;
		}
		i++;
	}
	va_end(value);
	return (count);
}
