/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_location.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:13:19 by fflores           #+#    #+#             */
/*   Updated: 2020/11/02 15:13:21 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	find_north(t_data *data, int i, int j)
{
	data->player.rotation_angel -= M_PI / 2;
	data->player.x = (i + 1) * TILE_SIZE;
	data->player.y = (j + 1) * TILE_SIZE;
	return (1);
}

static int	find_east(t_data *data, int i, int j)
{
	data->player.x = (i + 1) * TILE_SIZE;
	data->player.y = (j + 1) * TILE_SIZE;
	return (1);
}

static int	find_south(t_data *data, int i, int j)
{
	data->player.rotation_angel += M_PI / 2;
	data->player.x = (i + 1) * TILE_SIZE;
	data->player.y = (j + 1) * TILE_SIZE;
	return (1);
}

static int	find_west(t_data *data, int i, int j)
{
	data->player.rotation_angel += M_PI;
	data->player.x = (i + 1) * TILE_SIZE;
	data->player.y = (j + 1) * TILE_SIZE;
	return (1);
}

void		get_player_location(t_data *data)
{
	int i;
	int j;
	int detcted;

	j = -1;
	detcted = 0;
	while (++j < data->conf.map_h)
	{
		i = -1;
		while (data->conf.world_map[j][++i])
		{
			if (data->conf.world_map[j][i] == 'N')
				detcted += find_north(data, i, j);
			if (data->conf.world_map[j][i] == 'E')
				detcted += find_east(data, i, j);
			if (data->conf.world_map[j][i] == 'S')
				detcted += find_south(data, i, j);
			if (data->conf.world_map[j][i] == 'W')
				detcted += find_west(data, i, j);
		}
	}
	if (detcted > 1)
		ft_put_error("\nInvalid map\n", EINVAL);
	else if (detcted == 0)
		ft_put_error("\nInvalid map\n", EINVAL);
}
