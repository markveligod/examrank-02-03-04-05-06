#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_zone
{
    int width;
    int height;
    char backgrond;
} t_zone;

typedef struct s_list
{
	char	type;
	float	x;
	float	y;
	float	width;
	float	height;
	char	color;
} t_list;

int ft_strlen(char *str)
{
    int i = 0;

    if (!str)
        return (i);
    while (str[i])
        i++;
    return (i);
}

int fail(char *str)
{
    write(1, str, ft_strlen(str));
    return (1);
}

int free_all(FILE *file, char *draw)
{
    fclose(file);
    if (draw)
        free(draw);
    return (1);
}

int check_zone(t_zone *zone)
{
    return ((zone->width >= 0 && zone->width <= 300) && (zone->height >= 0 && zone->height <= 300));
}

char *get_zone(FILE *file, t_zone *zone)
{
    int count;
    char *array;
    int i = 0;

    if ((count = fscanf(file, "%d %d %c\n", &zone->width, &zone->height, &zone->backgrond)) != 3)
        return (NULL);
    if (count == (-1))
        return (NULL);
    if (!(check_zone(zone)))
        return (NULL);
    array = (char *)malloc(sizeof(char) * (zone->width * zone->height));
    while (i < zone->width * zone->height)
    {
        array[i] = zone->backgrond;
        i++;
    }
    return (array);
}

int check_tmp(t_list *tmp)
{
    return ((tmp->height > 0.00000000 && tmp->width > 0.00000000) && (tmp->type == 'r' || tmp->type == 'R'));
}

int is_rec(float y, float x, t_list *tmp)
{
    float check = 1.00000000;
    if ((x < tmp->x) || (tmp->x + tmp->width < x) || (y < tmp->y) || (tmp->y + tmp->height < y))
        return (0);
    if (((x - tmp->x) < check) || ((tmp->x + tmp->width) - x < check) || ((y - tmp->y) < check) || ((tmp->y + tmp->height) - y < check))
        return (2);
    return (1);
}

void get_draw(char **draw, t_list *tmp, t_zone *zone)
{
    int x, y;
    int rec;

    y = 0;
    while (y < zone->height)
    {
        x = 0;
        while (x < zone->width)
        {
            rec = is_rec(y, x, tmp);
            if ((tmp->type == 'r' && rec == 2) || (tmp->type == 'R' && rec))
                (*draw)[(y * zone->width) + x] = tmp->color;
            x++;
        }
        y++;
    }
}

int drawing(FILE *file, char **draw, t_zone *zone)
{
    t_list tmp;
    int count;

    while ((count = fscanf(file, "%c %f %f %f %f %c\n", &tmp.type, &tmp.x, &tmp.y, &tmp.width, &tmp.height, &tmp.color)) == 6)
    {
        if (!(check_tmp(&tmp)))
            return (0);
        get_draw(draw, &tmp, zone);
    }
    if (count != (-1))
        return (0);
    return (1);
}

void print_draw(char *draw, t_zone *zone)
{
    int i = 0;

    while (i < zone->height)
    {
        write(1, draw + (i * zone->width), zone->width);
        write(1, "\n", 1);
        i++;
    }
}

int main(int ac, char **av)
{
    FILE *file;
    char *draw;
    t_zone zone;

    if (ac != 2)
        return (fail("Error: argument\n"));
    if (!(file = fopen(av[1], "r")))
        return (fail("Error: Operation file corrupted\n"));
    if (!(draw = get_zone(file, &zone)))
        return (free_all(file, NULL) && fail("Error: Operation file corrupted\n"));
    if (!(drawing(file, &draw, &zone)))
        return (free_all(file, draw) && fail("Error: Operation file corrupted\n"));
    print_draw(draw, &zone);
    free_all(file, draw);
    return (0);
}