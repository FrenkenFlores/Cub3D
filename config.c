#include "cub3d.h"

void	start(t_data *data)
{
	data->player.x = 0;
	data->player.y = 0;
	data->player.radius = 16;
	data->player.rotation_angel = 0;
	data->player.move_speed = 7.0;
	data->player.rotation_speed = 7 * (M_PI / 180);
	data->conf.map_h = -1;
	data->conf.map_on_off = 0;
	data->conf.map_size = 0.3;
	data->conf.world_map = NULL;
	data->conf.floor_color = -1;
	data->conf.ceill_color = -1;
	data->sprite = NULL;
	data->save = 0;
	data->conf.num_sprites = 0;
}

int		get_map(char **ptr, t_data *data)
{
	int j;
	int i;

	j = data->conf.str_num - 1;
	while (j > 0)
	{
		i = 0;
		while (i < ft_strlen(ptr[j]))
		{
			if (ptr[j][i] == ' ' || ptr[j][i] == '0' || ptr[j][i] == '1' || ptr[j][i] == '2'
			|| ptr[j][i] == 'N' || ptr[j][i] == 'E' || ptr[j][i] == 'S' || ptr[j][i] == 'W')
				i++;
			else
				break;
		}
		if (i != ft_strlen(ptr[j]))
			break;
		j--;
	}
	data->conf.world_map = &ptr[++j];
	if (j == 0)
		ft_put_error("\nMap dose not exist\n", EINVAL);
	return (data->conf.str_num - j);
}

char	**getinfo(t_list **list, size_t elm_count)
{
	char	**ptr;
	t_list	*tmp;
	size_t	j;
	int	i = 0;

	tmp = *list;
	j = elm_count;
	ptr = (char**)malloc((sizeof(char*) * j) + 2);
	while (tmp && j >= 0)
	{
		ptr[j - 1] = tmp->content;
		tmp = tmp->next;
		j--;
	}
	ptr[elm_count++] = "";
	ptr[elm_count] = NULL;
	return (ptr);
}

void	get_textures(t_data *data)
{
	data->tex[0].img_ptr = mlx_xpm_file_to_image(data->mlx, data->conf.path_north, &data->tex[0].width, &data->tex[0].height);
	data->tex[0].img_addr = mlx_get_data_addr(data->tex[0].img_ptr, &data->tex[0].bits_per_pixel, &data->tex[0].line_length, &data->tex[0].endian);
	data->tex[1].img_ptr = mlx_xpm_file_to_image(data->mlx, data->conf.path_east, &data->tex[1].width, &data->tex[1].height);
	data->tex[1].img_addr = mlx_get_data_addr(data->tex[1].img_ptr, &data->tex[1].bits_per_pixel, &data->tex[1].line_length, &data->tex[1].endian);
	data->tex[2].img_ptr = mlx_xpm_file_to_image(data->mlx, data->conf.path_south, &data->tex[2].width, &data->tex[2].height);
	data->tex[2].img_addr = mlx_get_data_addr(data->tex[2].img_ptr, &data->tex[2].bits_per_pixel, &data->tex[2].line_length, &data->tex[2].endian);
	data->tex[3].img_ptr = mlx_xpm_file_to_image(data->mlx, data->conf.path_west, &data->tex[3].width, &data->tex[3].height);
	data->tex[3].img_addr = mlx_get_data_addr(data->tex[3].img_ptr, &data->tex[3].bits_per_pixel, &data->tex[3].line_length, &data->tex[3].endian);
	data->tex[4].img_ptr = mlx_xpm_file_to_image(data->mlx, data->conf.path_sprite, &data->tex[4].width, &data->tex[4].height);
	data->tex[4].img_addr = mlx_get_data_addr(data->tex[4].img_ptr, &data->tex[4].bits_per_pixel, &data->tex[4].line_length, &data->tex[4].endian);
}