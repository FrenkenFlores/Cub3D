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
	data->conf.map_on_off = 1;
	data->conf.map_size = 0.3;
	data->conf.world_map = NULL;
	data->conf.floor_color = -1;
	data->conf.ceill_color = -1;
	data->sprite = NULL;
	data->save = 0;
}
size_t	make_list(int fd, t_list **list)
{
	char	*str;
	size_t	i;

	i = 0;
	*list = NULL;
	while(get_next_line(fd, &str))
	{
		*list = push_back(str, *list);
		i++;
	}
	*list = push_back(str, *list);
	i++;
	return (i);
}
t_list	*push_back(char *str, t_list *old_list)
{
	t_list	*new_list;

	if (!(new_list = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	new_list->content = str;
	new_list->next = old_list;
	return (new_list);
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
			{
				data->player.rotation_angel -= M_PI / 2;
				data->player.x = (i + 1) * TILE_SIZE;
				data->player.y = (j + 1) * TILE_SIZE;
				detcted++;
			}
			if (data->conf.world_map[j][i] == 'E')			
			{
				data->player.x = (i + 1) * TILE_SIZE;
				data->player.y = (j + 1) * TILE_SIZE;
				detcted++;
			}
			if (data->conf.world_map[j][i] == 'S')			
			{
				data->player.rotation_angel += M_PI / 2;
				data->player.x = (i + 1) * TILE_SIZE;
				data->player.y = (j + 1) * TILE_SIZE;
				detcted++;
			}
			if (data->conf.world_map[j][i] == 'W')			
			{
				data->player.rotation_angel += M_PI;
				data->player.x = (i + 1) * TILE_SIZE;
				data->player.y = (j + 1) * TILE_SIZE;
				detcted++;
			}
			if (detcted > 1)
			ft_put_error("\nRestricted to have more then one orientation on the map\n", EINVAL);		
			i++;
		}
		j++;
	}
}

void	get_resolution(char **str, t_data *data, size_t elm_count)
{
	size_t	j;
	size_t i;
	
	j = 0;
	while (j < elm_count)
	{
		i = 0;
		while (i < ft_strlen(str[j]))
		{
			if (str[j][i] == 'R')
			{
				i++;
				while (str[j][i] == ' ')
					i++;
				data->conf.win_w = ft_atoi(str[j] + i);
				i += ft_numsize(data->conf.win_w);
				while (str[j][i] == ' ')
					i++;
				data->conf.win_h = ft_atoi(str[j] + i);
			}
			i++;
		}
		j++;
	}
	if (!(data->conf.win_h) || !(data->conf.win_w))
		ft_put_error("\nInvalid resolution parameters\n", EINVAL);
}

void	get_floor_ceilling(char **str, t_data *data, size_t elm_count)
{
	size_t	j;
	size_t i;
	int r;
	int g;
	int b;
	
	j = 0;
	while (j < elm_count)
	{
		i = 0;
		while (i < ft_strlen(str[j]))
		{
			if (str[j][i] == 'F' && str[j][i + 1] == ' ')
			{
				i += 1;
				while (str[j][i] == ' ')
					i++;
				r = ft_atoi(str[j] + i++);
				i += ft_numsize(r);
				g = ft_atoi(str[j] + i++);
				i += ft_numsize(g);
				b = ft_atoi(str[j] + i);
				data->conf.floor_color = rgb_hex(r, g, b);
				continue;
			}
			if (str[j][i] == 'C' && str[j][i + 1] == ' ')
			{
				i += 1;
				while (str[j][i] == ' ')
					i++;
				r = ft_atoi(str[j] + i++);
				i += ft_numsize(r);
				g = ft_atoi(str[j] + i++);
				i += ft_numsize(g);
				b = ft_atoi(str[j] + i);
				data->conf.ceill_color = rgb_hex(r, g, b);
				continue;
			}
			i++;
		}
		j++;
	}
	if (!(data->conf.path_east) || !(data->conf.path_west) || !(data->conf.path_south) || !(data->conf.path_north))
		ft_put_error("\nDid not find the wall textures\n", EINVAL);
}

void	get_tex_path(char **str, t_data *data, size_t elm_count)
{
	size_t	j;
	size_t i;
	
	j = 0;
	while (j < elm_count)
	{
		i = 0;
		while (i < ft_strlen(str[j]))
		{
			if (str[j][i] == 'N' && str[j][i + 1] == 'O')
			{
				i += 2;
				while (str[j][i] == ' ')
					i++;
				data->conf.path_north = &(str[j][i]);
			}
			if (str[j][i] == 'S' && str[j][i + 1] == 'O')
			{
				i += 2;
				while (str[j][i] == ' ')
					i++;
				data->conf.path_south = &(str[j][i]);
			}
			if (str[j][i] == 'S' && str[j][i + 1] == ' ')
			{
				i += 1;
				while (str[j][i] == ' ')
					i++;
				data->conf.path_sprite = &(str[j][i]);
			}
			if (str[j][i] == 'W' && str[j][i + 1] == 'E')
			{
				i += 2;
				while (str[j][i] == ' ')
					i++;
				data->conf.path_west = &(str[j][i]);
			}
			if (str[j][i] == 'E' && str[j][i + 1] == 'A')
			{
				i += 2;
				while (str[j][i] == ' ')
					i++;
				data->conf.path_east = &(str[j][i]);
			}
			i++;
		}
		j++;
	}
	if (!(data->conf.path_east) || !(data->conf.path_west) || !(data->conf.path_south) || !(data->conf.path_north))
		ft_put_error("\nDid not find the wall textures\n", EINVAL);
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
	data->tex[0].img_ptr = mlx_xpm_file_to_image(data->mlx, data->conf.path_north, &data->tex[0].width, &data->tex[0].height);	//N
	data->tex[0].img_addr = mlx_get_data_addr(data->tex[0].img_ptr, &data->tex[0].bits_per_pixel, &data->tex[0].line_length, &data->tex[0].endian);
	data->tex[1].img_ptr = mlx_xpm_file_to_image(data->mlx, data->conf.path_east, &data->tex[1].width, &data->tex[1].height);	//E
	data->tex[1].img_addr = mlx_get_data_addr(data->tex[1].img_ptr, &data->tex[1].bits_per_pixel, &data->tex[1].line_length, &data->tex[1].endian);
	data->tex[2].img_ptr = mlx_xpm_file_to_image(data->mlx, data->conf.path_south, &data->tex[2].width, &data->tex[2].height);	//S
	data->tex[2].img_addr = mlx_get_data_addr(data->tex[2].img_ptr, &data->tex[2].bits_per_pixel, &data->tex[2].line_length, &data->tex[2].endian);
	data->tex[3].img_ptr = mlx_xpm_file_to_image(data->mlx, data->conf.path_west, &data->tex[3].width, &data->tex[3].height);	//W
	data->tex[3].img_addr = mlx_get_data_addr(data->tex[3].img_ptr, &data->tex[3].bits_per_pixel, &data->tex[3].line_length, &data->tex[3].endian);
	data->tex[4].img_ptr = mlx_xpm_file_to_image(data->mlx, data->conf.path_sprite, &data->tex[4].width, &data->tex[4].height);	//FLOOR
	data->tex[4].img_addr = mlx_get_data_addr(data->tex[4].img_ptr, &data->tex[4].bits_per_pixel, &data->tex[4].line_length, &data->tex[4].endian);
}