#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

typedef struct drawing drawing, *Pdrawing;

struct drawing {
    int width;
    int height;
    char * matrice;
};

typedef struct circle circle, *Pcircle;

struct circle {
    char type;
    float x;
    float y;
    float radius;
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
	int 	scan_ret;
	char	*tmp;
	int		i;
	char	background;

	scan_ret = fscanf(file,"%d %d %c\n", &drawing->width, &drawing->height, &background);
	if (scan_ret == 3)
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

float square(float a)
{
	return (a * a);
}

float sq_dist(float x1, float y1, float x2, float y2)
{
	float dist_x;
	float dist_y;

	dist_x = square(x1 - x2);
	dist_y = square(y1 - y2);
	return (dist_x + dist_y);
}

int is_in_circle(float x, float y, circle *circle)
{
	float	distance;
	float	distance_sqrt;

	distance_sqrt = sqrtf(sq_dist(x, y, circle->x, circle->y));
	distance = distance_sqrt - circle->radius;
	if (distance <= 0.00000000)
	{
		if (distance <= -1.00000000)
			return (1); // Inside
		return (2); // Border
	}
	return (0);
}

void execute_one(circle *circle, drawing *drawing, int x, int y)
{
	int is_in;

	is_in = is_in_circle((float)x, (float)y, circle);
	if ((is_in == 2) || ((is_in == 1 && (circle->type == 'C'))))
		drawing->matrice[x + y * drawing->width] = circle->color;
}

int apply_op(circle *circle, drawing *drawing)
{
	int j;
	int i;

	if ((circle->radius <= 0.00000000) || ((circle->type != 'C' && (circle->type != 'c'))))
		return (1);
	i = 0;
	while (i < drawing->width)
	{
		j = 0;
		while (j < drawing->height)
			execute_one(circle, drawing, i, j++);
		i++;
	}
	return (0);
}

int print_info(drawing *drawing)
{
	int i;

	i = 0;
	while (i < drawing->height)
	{
		printf("%.*s\n", drawing->width, drawing->matrice + i * drawing->width);
		i = i + 1;
	}
	return i;
}

int execute(FILE *file)
{
	int 	scan_ret;
	circle 	circle;
	drawing	drawing;

	if (!get_info(file, &drawing))
	{
		scan_ret = fscanf(file,"%c %f %f %f %c\n", &circle.type, &circle.x, &circle.y, &circle.radius, &circle.color);
		while (scan_ret == 5)
		{
			if (apply_op(&circle, &drawing))
				return (1);
			scan_ret = fscanf(file,"%c %f %f %f %c\n", &circle.type, &circle.x, &circle.y, &circle.radius, &circle.color);
		}
		if (scan_ret == -1)
		{
			print_info(&drawing);
			return (0);
		}
		return (1);
	}
	return (1);
}

int main(int argc,char **argv)
{
	int i;
	FILE *file;

	if (argc == 2)
	{
		file = fopen(argv[1], "r");
		if (file && !execute(file))
			return (0);
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