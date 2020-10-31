#include "cub3d.h"

int		ft_min(int a, int b)
{
	return((a < b) ? a : b);
}

int		ft_max(int a, int b)
{
	return((a > b) ? a : b);
}

int		ft_numsize(int num)
{
	int size;

	size = 1;
	while(num / 10)
	{
		num = num / 10;
		size++;
	}
	return(size);
}

float normalize_angle(double angle)
{
	double alpha;

	alpha = angle;
	while (alpha >= 2 * M_PI)
		alpha = alpha - 2 * M_PI;
	while (alpha < 0)
		alpha = alpha + 2 * M_PI;
	return ((float)alpha);
}


size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 == *s2 && *s1 != '\0' && *s2 != '\0' && n > 1)
	{
	s1++;
	s2++;
	n--;
	}
	return (*(unsigned char*)s1 - *(unsigned char*)s2);
}

void	mlx_pix_put(t_data *data, int x, int y, int color)
{
	char	*pos;
	int		offset;

	offset = y * data->img.line_length + x * (data->img.bits_per_pixel / 8);
	pos = data->img.img_addr + offset;
	*(unsigned int*)pos = color;
}

void	rect(t_data *data, double x, double y, int rect_width, int rect_height, int color)
{
	int i;
	int j;

	j = 0;
	while(j <= rect_height)
	{
		i = 0;
		while (i <= rect_width)
		{
			mlx_pix_put(data, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

void	circle(t_data *data, double x, double y, double radius, int color)
{
	int i;
	int j;

	j = -1 * radius;
	while(j <= radius)
	{
		i = -1 * radius;
		while (i <= radius)
		{
			if (i * i <= radius * radius - j * j)
				mlx_pix_put(data, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

void	line(t_data *data, double x1, double y1, double x2, double y2, int color)
{
	double i;
	double j;
	double alpha;

	alpha = (y2 - y1) / (x2 - x1);
	j = 0;
	while ((j <= y2 - y1) && y2 >= y1)
	{
		i = 0;
		while ((i <= x2 - x1) && x2 >= x1)
		{
			if (j >= alpha * i - 1 && j <= alpha * i + 1)
				mlx_pix_put(data, x1 + i, y1 + j, color);
			i++;

		}
		while ((i <= x1 - x2) && x2 < x1)
		{
			if (j >= alpha * -1 * i - 1 && j <= alpha * -1 *i + 1)
				mlx_pix_put(data, x1 - i, y1 + j, color);
			i++;
		}
		j++;
	}
	while ((j <= y1 - y2) && y2 < y1)
	{
		i = 0;
		while ((i <= x2 - x1) && x2 >= x1)
		{
			if (j >= alpha * - 1 * i - 1 && j <= alpha * -1 * i + 1)
				mlx_pix_put(data, x1 + i, y1 - j, color);
			i++;
		}
		while ((i <= x1 - x2) && x2 < x1)
		{
			if (j >= alpha * i - 1 && j <= alpha * i + 1)
				mlx_pix_put(data, x1 - i, y1 - j, color);
			i++;
		}
		j++;
	}
}

unsigned long rgb_hex(int r, int g, int b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

double calculate_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
int		point_in_vert_segment(t_data * data, t_ray *ray, t_sprite *sprite, int column_id)
{
	double x;
	double y;
	double angle;

	angle = (double)tan(abs(ray->wall_hit_y - data->player.y) / (double)abs(ray->wall_hit_x - data->player.x));
	if (sprite->x1 == sprite->x2
	&& ((ray->wall_hit_y - data->player.y) / (ray->wall_hit_x - data->player.x)) >= ((ft_min(sprite->y1, sprite->y2) - data->player.y) / sprite->distance)
	&& ((ray->wall_hit_y - data->player.y) / (ray->wall_hit_x - data->player.x)) <= ((ft_max(sprite->y1, sprite->y2) - data->player.y) / sprite->distance)
	&& x >= ft_min(data->player.x, ray->wall_hit_x) && x <= ft_max(data->player.x, ray->wall_hit_x))
	{
		data->rays[column_id]->hit_sprite = (sprite->distance * angle) + TILE_SIZE / 2.1;
		return (1);
	}
	return (0);
}

int		point_in_horz_segment(t_data * data, t_ray *ray, t_sprite *sprite, int column_id)
{
	double x;
	double y;
	double angle;

	angle = (double)tan(abs(ray->wall_hit_x - data->player.x) / (double)abs(ray->wall_hit_y - data->player.y));
	x = ft_min(sprite->x1, sprite->x2);
	y = ft_min(sprite->y1, sprite->y2);
	if (sprite->y1 == sprite->y2
	&& ((ray->wall_hit_x - data->player.x) / (ray->wall_hit_y - data->player.y)) >= ((ft_min(sprite->x1, sprite->x2) - data->player.x) / sprite->distance)
	&& ((ray->wall_hit_x - data->player.x) / (ray->wall_hit_y - data->player.y)) <= ((ft_max(sprite->x1, sprite->x2) - data->player.x) / sprite->distance)
	&& y >= ft_min(data->player.y, ray->wall_hit_y) && y <= ft_max(data->player.y, ray->wall_hit_y))
	{
		data->rays[column_id]->hit_sprite = (sprite->distance * angle) + TILE_SIZE / 2.1;
		return (1);
	}
	return (0);
}

int		point_in_segment(t_data * data, t_ray *ray, t_sprite *sprite, int column_id)
{
	double x;
	double y;
	double a;
	double b;
	double slope;
	double slope_2;

	a = abs(data->player.x - ray->wall_hit_x);
	b = abs(data->player.y - ray->wall_hit_y);
	slope = b / a;
	slope_2 = (double)abs(sprite->y2 - sprite->y1) / abs(sprite->x2 - sprite->x1);
	x = ft_min(sprite->x1, sprite->x2);
	y = ft_min(sprite->y1, sprite->y2);
	while ((int)y <= ft_max(sprite->y1, sprite->y2))
	{
		x = ft_min(sprite->x1, sprite->x2);
		while ((int)x <= ft_max(sprite->x1, sprite->x2))
		{
			if ((abs(ray->wall_hit_y - y) >= (slope * abs(ray->wall_hit_x - x)) - 5 && abs(ray->wall_hit_y - y) <= (slope * abs(ray->wall_hit_x - x)) + 5)
			&& (abs(sprite->y2 - y) >= (slope_2 * abs(sprite->x2 - x)) - 5 && abs(sprite->y2 - y) <= (slope_2 * abs(sprite->x2 - x)) + 5)
			&& x >= ft_min(data->player.x, ray->wall_hit_x) && x <= ft_max(data->player.x, ray->wall_hit_x)
			&& y >= ft_min(data->player.y, ray->wall_hit_y) && y <= ft_max(data->player.y, ray->wall_hit_y))
			{
				ray->hit_sprite = sqrtl((x - ft_min(sprite->x1, sprite->x2)) * (x - ft_min(sprite->x1, sprite->x2)) + (y - ft_min(sprite->y1, sprite->y2)) * (y - ft_min(sprite->y1, sprite->y2)));
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}