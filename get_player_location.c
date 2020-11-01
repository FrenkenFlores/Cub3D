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

static void check(int detcted)
{
	if (detcted > 1)
		ft_put_error("\nRestricted to have more then one orientation on the map\n", EINVAL);
	else if (detcted == 0)
		ft_put_error("\nThere is no player on the map\n", EINVAL);
}

void	get_player_location(t_data *data)
{
	int i;
	int j;
	int detcted;

	j = 0;
	detcted = 0;
	while (j < data->conf.map_h)
	{
		i = 0;
		while (data->conf.world_map[j][i])
		{
			if (data->conf.world_map[j][i] == 'N')			
				detcted += find_north(data, i, j);
			if (data->conf.world_map[j][i] == 'E')			
				detcted += find_east(data, i, j);
			if (data->conf.world_map[j][i] == 'S')			
				detcted += find_south(data, i, j);
			if (data->conf.world_map[j][i] == 'W')			
				detcted += find_west(data, i, j);
			i++;
		}
		j++;
	}
	check(detcted);
}