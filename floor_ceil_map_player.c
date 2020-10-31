#include "cub3d.h"

void	render_ceilling_floor(t_data *data)
{
	rect(data, 0, 0, data->conf.win_w, data->conf.win_h, data->conf.ceill_color);
	rect(data, 0, data->conf.win_h / 2, data->conf.win_w, data->conf.win_h, data->conf.floor_color);
}
void	render_map(t_data *data)
{
	int i = 0;
	int j = 0;
	while (j < data->conf.map_h)
	{
		i = 0;
		while (data->conf.world_map[j][i])
		{
			if (data->conf.world_map[j][i] == '1' && data->conf.map_on_off == 1)
				rect(data, i * TILE_SIZE * data->conf.map_size, j * TILE_SIZE * data->conf.map_size, TILE_SIZE * data->conf.map_size, TILE_SIZE * data->conf.map_size, 0xFFFFFF);
			else if (data->conf.world_map[j][i] != '1' && data->conf.world_map[j][i] != ' ' && data->conf.map_on_off == 1)
				rect(data, i * TILE_SIZE * data->conf.map_size, j * TILE_SIZE * data->conf.map_size, TILE_SIZE * data->conf.map_size, TILE_SIZE * data->conf.map_size, 0xAAAAAA);
			i++;
		}
		j++;
	}
}
void	render_player(t_data *data)
{	
	if (data->conf.map_on_off == 1)
		circle(data, data->player.x * data->conf.map_size, data->player.y * data->conf.map_size, data->player.radius * data->conf.map_size, 0x212121);
}