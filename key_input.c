/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:37:38 by fflores           #+#    #+#             */
/*   Updated: 2020/11/02 15:37:40 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_pl_xy(t_data *data, double new_x, double new_y)
{
	data->player.y = new_y;
	data->player.x = new_x;
}

void		key_input(int keycode, t_data *data)
{
	double	new_x;
	double	new_y;

	new_y = data->player.y;
	new_x = data->player.x;
	if (keycode == 13)
	{
		new_y += sin(data->player.rotation_angel) * data->player.move_speed;
		new_x += cos(data->player.rotation_angel) * data->player.move_speed;
	}
	if (keycode == 1)
	{
		new_y -= sin(data->player.rotation_angel) * data->player.move_speed;
		new_x -= cos(data->player.rotation_angel) * data->player.move_speed;
	}
	if (keycode == 0)
		data->player.rotation_angel -= data->player.rotation_speed;
	if (keycode == 2)
		data->player.rotation_angel += data->player.rotation_speed;
	if (keycode == 53)
		mlx_close(data);
	if (safe_distance(data, new_x, new_y) != -1)
		init_pl_xy(data, new_x, new_y);
}

int			mlx_close(t_data *data)
{
	if (data == 0)
		exit(EXIT_SUCCESS);
	mlx_destroy_window(data->mlx, data->mlx_win);
	exit(EXIT_SUCCESS);
}

int			safe_distance(t_data *data, double player_x, double player_y)
{
	int		i;
	int		j;
	double	radius;

	radius = data->player.radius - 10;
	j = -1 * radius;
	while (j <= radius)
	{
		i = -1 * radius;
		while (i <= radius)
		{
			if (i * i < radius * radius - j * j)
			{
				if (is_wall(data, player_x + i, player_y + j))
					return (-1);
			}
			i++;
		}
		j++;
	}
	return (1);
}
