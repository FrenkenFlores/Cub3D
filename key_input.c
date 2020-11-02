#include "cub3d.h"

void	key_input(int keycode, t_data *data)
{
	int i;
	int j;
	double	player_new_x;
	double	player_new_y;	

	i = 0;
	j = -1 * data->player.radius;
	player_new_y = data->player.y;
	player_new_x = data->player.x;
	if (keycode == 13)
	{
		player_new_y += sin(data->player.rotation_angel) * data->player.move_speed;
		player_new_x += cos(data->player.rotation_angel) * data->player.move_speed;
	}
	if (keycode == 1)
	{
		player_new_y -= sin(data->player.rotation_angel) * data->player.move_speed;
		player_new_x -= cos(data->player.rotation_angel) * data->player.move_speed;
	}
	if (keycode == 0)
		data->player.rotation_angel -= data->player.rotation_speed;
	if (keycode == 2)
		data->player.rotation_angel += data->player.rotation_speed;
	if (keycode == 53)
		mlx_close(data);
	if (safe_distance(data, player_new_x, player_new_y) != -1)
	{
		data->player.y = player_new_y;
		data->player.x = player_new_x;
	}
}

void	mlx_close(t_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	exit(EXIT_SUCCESS);
}

int		safe_distance(t_data *data, double player_x, double player_y)
{
	int i;
	int j;
	double radius;

	radius = data->player.radius - 10;
	j = -1 * radius;
	while(j <= radius)
	{
		i = -1 * radius;
		while(i <= radius)
		{
			if (i * i < radius * radius - j * j)
			{
				if (is_wall(data, player_x + i, player_y + j))
					return -1;			}
			i++;
		}
		j++;
	}
	return (1);
}