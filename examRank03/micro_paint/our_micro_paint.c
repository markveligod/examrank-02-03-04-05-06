#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct drawing drawing, *Pdrawing;

struct drawing {
    int width;
    int height;
    char * matrice;
};

typedef struct rectangle rectangle, *Prectangle;

struct rectangle {
    char type;
    float x;
    float y;
    float width;
    float height;
    char color;
};

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int get_info(FILE *file, drawing *drawing)
{
	char 	*tmp;
	int 	i;
	char	background;

	if (fscanf(file, "%d %d %c\n", &drawing->width, &drawing->height, &background) == 3)
	{
		if ((((drawing->width < 1) || (300 < drawing->width)) || (drawing->height < 1)) || (300 < drawing->height))
			return (1);
		tmp = (char *)malloc(drawing->width * drawing->height);
		drawing->matrice = tmp;
		if (!drawing->matrice)
			return (1);
		i = 0;
		while (i < drawing->width * drawing->height)
			drawing->matrice[i++] = background;
		return (0);
	}
	return (1);
}

int is_in_rectangle(float x, float y, rectangle *rectangle)
{
	if ((((x < rectangle->x) || (rectangle->x + rectangle->width < x)) || (y < rectangle->y)) || (rectangle->y + rectangle->height < y))
		return (0);
	if (((x - rectangle->x < 1.00000000) || ((rectangle->x + rectangle->width) - x < 1.00000000)) ||
		((y - rectangle->y < 1.00000000 || ((rectangle->y + rectangle->height) - y < 1.00000000))))
		return (2); // Border
	return (1); // Inside
}

void execute_one(rectangle *rect, drawing *drawing, int x, int y)
{
	int is_in;

	is_in = is_in_rectangle((float)x, (float)y, rect);
	if ((is_in == 2) || ((is_in == 1 && (rect->type == 'R'))))
		drawing->matrice[x + y * drawing->width] = rect->color;
	return;
}

int apply_op(rectangle *rect,drawing *drawing)
{
	int j;
	int i;

	if (((rect->width <= 0.00000000) || (rect->height <= 0.00000000)) || ((rect->type != 'R' && (rect->type != 'r'))))
		return (1);
	i = 0;
	while (i < drawing->width)
	{
		j = 0;
		while (j < drawing->height)
			execute_one(rect, drawing, i, j++);
		i++;
	}
	return (0);
}

void print_info(drawing *zone)
{
	int i;

	i = 0;
	while (i < zone->height)
		printf("%.*s\n", zone->width, zone->matrice + i++ * zone->width);
}

int execute(FILE *file)
{
	int 		scan_ret;
	rectangle	rect;
	drawing		drawing;

	if (!get_info(file, &drawing))
	{
		scan_ret = fscanf(file,"%c %f %f %f %f %c\n", &rect.type, &rect.x, &rect.y, &rect.width, &rect.height, &rect.color);
		while (scan_ret == 6)
		{
			if (apply_op(&rect, &drawing))
				return (1);
			scan_ret = fscanf(file,"%c %f %f %f %f %c\n", &rect.type, &rect.x, &rect.y, &rect.width, &rect.height, &rect.color);
		}
		if (scan_ret == -1)
		{
			print_info(&drawing);
			return (0);
		}
	}
	return (1);
}

int main(int argc, char **argv)
{
	int  	i;
	FILE	*file;

	if (argc == 2)
	{
		file = fopen(argv[1],"r");
		if (file && !execute(file))
			return 0;
		i = ft_strlen("Error: Operation file corrupted\n");
		write(1, "Error: Operation file corrupted\n", i);
	}
	else
	{
		i = ft_strlen("Error: argument\n");
		write(1, "Error: argument\n", i);
	}
	return (1);
}