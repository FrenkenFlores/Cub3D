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

void		ft_put_error(char *s, int id)
{
	if (!s)
		return ;
	errno = id;
	perror("Error ");
	write(2, s, ft_strlen(s));
	exit(EXIT_FAILURE);
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
//			mlx_pixel_put(data->mlx, data->mlx_win, x + i, y + j, color);
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
//				mlx_pixel_put(data->mlx, data->mlx_win, x + i, y + j, color);
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

int		is_wall(t_data *data, double x, double y)
{
	int map_index_x;
	int map_index_y;

	map_index_x = (int)(x / TILE_SIZE);
	map_index_y = (int)(y / TILE_SIZE);
	if (map_index_x < 0 || map_index_x > data->conf.win_w || map_index_y < 0 || map_index_y > data->conf.win_h || map_index_y >= data->conf.map_h)
			return (-1);
	if (ft_strlen(data->conf.world_map[map_index_y]) > map_index_x)
		return (data->conf.world_map[map_index_y][map_index_x] == '1' ? 1 : 0);
	return (-1);
}

void	check_error_save(t_data *data, int argc, char **argv, int fd)
{
	if (argc < 2)
		ft_put_error("\nToo few arguments\n", EINVAL);
	if (argc > 2 && ((ft_strncmp(argv[2],"--save", ft_strlen("--save")) != 0) || (ft_strlen(argv[2]) != ft_strlen("--save"))))
		ft_put_error("\nOnly --save flag is allowed\n", EINVAL);
	else 
		data->save = 1;
	if (argc >= 2 && (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 2)) != 0)
		ft_put_error("\nInvalid file\n", EINVAL);
	if (fd < 0)
		ft_put_error("\nCan not open file\n", EINVAL);
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

unsigned long rgb_hex(int r, int g, int b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
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



void	get_textpath(char **str, t_data *data, size_t elm_count)
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
//	printf("%s\n", data->conf.path_sprite);
	if (!(data->conf.path_east) || !(data->conf.path_west) || !(data->conf.path_south) || !(data->conf.path_north))
		ft_put_error("\nDid not find the wall textures\n", EINVAL);
}

void	start(t_data *data)
{
	data->player.x = 0;
	data->player.y = 0;
	data->player.turn_direction = 0;   // +1 : right, -1 : left
	data->player.walk_directoin = 0;  // +1 : forward, -1 : backward
	data->player.radius = 16;
	data->player.rotation_angel = 0;
	data->player.move_speed = 7.0;
	data->player.rotation_speed = 7 * (M_PI / 180);
/*	data->ray.angel = 0; //data->player.rotation_angel - (FOV_ANGLE / 2)
	data->ray.wall_hit_x = 0;
	data->ray.wall_hit_y = 0;
	data->ray.distance = 0;
	data->ray.point_down = 0;
	data->ray.point_up = 0;
	data->ray.point_left = 0;
	data->ray.point_right = 0;
	data->ray.ray_hit_vertical_wall = 0;
*/	data->conf.map_h = -1;
	data->conf.map_w = -1;
	data->conf.map_size = 0.6;
	data->conf.world_map = NULL;
	data->conf.floor_color = -1;
	data->conf.ceill_color = -1;
	data->sprite = NULL;
	data->save = 0;
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


int		check_position(char **world_map, int j, int i)
{
	if (world_map[j][i] != '1' && world_map[j][i] != '2' && world_map[j][i] != '0'
	&& world_map[j][i] != 'N' && world_map[j][i] != 'E' && world_map[j][i] != 'S'
	&& world_map[j][i] != 'W')
		return (-1);
	return (1);
}

int		check_zeros(char **world_map, int j, int i)
{
	if (check_position(world_map, j - 1, i - 1) == -1)
		return (-1);
	if (check_position(world_map, j - 1, i) == -1)
		return (-1);
	if (check_position(world_map, j - 1, i + 1) == -1)
		return (-1);
	if (check_position(world_map, j, i - 1) == -1)
		return (-1);
	if (check_position(world_map, j, i + 1) == -1)
		return (-1);
	if (check_position(world_map, j + 1, i - 1) == -1)
		return (-1);
	if (check_position(world_map, j + 1, i) == -1)
		return (-1);
	if (check_position(world_map, j + 1, i + 1) == -1)
		return (-1);
	return (1);
}


void	check_map(t_data *data)
{
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	while(j < data->conf.map_h)
	{
		i = 0;
		len = ft_strlen(data->conf.world_map[j]);
		while(i < len)
		{
			if (data->conf.world_map[j][i] == '0' && (check_zeros(data->conf.world_map, j, i) == -1))
				ft_put_error("\nInvalid map\n", EINVAL);
			i++;
		}
		j++;
	}
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

void	render_map(t_data *data)
{
	int i = 0;
	int j = 0;
	while (j < data->conf.map_h)
	{
		i = 0;
		while (data->conf.world_map[j][i])
		{
			if (data->conf.world_map[j][i] == '1')
				rect(data, i * TILE_SIZE * data->conf.map_size, j * TILE_SIZE * data->conf.map_size, TILE_SIZE * data->conf.map_size, TILE_SIZE * data->conf.map_size, 0xFFFFFF);
			else if (data->conf.world_map[j][i] != '1' && data->conf.world_map[j][i] != ' ')
				rect(data, i * TILE_SIZE * data->conf.map_size, j * TILE_SIZE * data->conf.map_size, TILE_SIZE * data->conf.map_size, TILE_SIZE * data->conf.map_size, 0xAAAAAA);
			i++;
		}
		j++;
	}
}

void	render_player(t_data *data)
{	
	circle(data, data->player.x * data->conf.map_size, data->player.y * data->conf.map_size, data->player.radius * data->conf.map_size, 0x212121);
}

void	free_rays_array(t_data *data)
{
	int i;

	i = 0;
	while (i < data->conf.num_rays)
	{
		if (data->rays[i])
			free (data->rays[i]);
		i++;
	}
	free (data->rays);
}

void	ray_pointer(t_ray *ray)
{
	ray->point_down = (ray->angel >= 0 && ray->angel < M_PI) ? 1 : 0;
	ray->point_up = !ray->point_down;
	ray->point_left = (ray->angel >= M_PI / 2 && ray->angel < 3 * M_PI / 2) ? 1 : 0;
	ray->point_right = !ray->point_left;
}

double calculate_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
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


int	ray_vert_hit_sprite(t_ray ray, t_data *data)
{
	ray.found_vert_hit_sprite = 0;
	ray.x_intercept = (int)(data->player.x / TILE_SIZE) * TILE_SIZE;
	ray.x_intercept += (ray.point_right) ? TILE_SIZE : 0;
	ray.y_intercept = data->player.y + (ray.x_intercept - data->player.x) * tan(ray.angel);
	ray.x_step = TILE_SIZE;
	ray.x_step *= (ray.point_left) ? -1 : 1;
	ray.y_step = TILE_SIZE * tan(ray.angel);
	ray.y_step *= (ray.point_up && ray.y_step > 0) ? -1 : 1;
	ray.y_step *= (ray.point_down && ray.y_step < 0) ? -1 : 1;
	ray.next_vert_x = ray.x_intercept;
	ray.next_vert_y = ray.y_intercept;
	ray.vert_wall_hit_x = 0;
	ray.vert_wall_hit_y = 0;
	while (ray.found_vert_hit_sprite == 0)
	{
		if (ray.next_vert_y > 0 && is_sprite(data, ray.next_vert_x - (ray.point_left ? 1 : 0), ray.next_vert_y) == 1 && (ray.next_vert_y > 0 && is_wall(data, ray.next_vert_x - (ray.point_left ? 1 : 0), ray.next_vert_y) != 1))
		{
			ray.vert_wall_hit_x = ray.next_vert_x;
			ray.vert_wall_hit_y = ray.next_vert_y;
			ray.found_vert_hit_sprite = 1;
			return (1);
		}
		else if (is_sprite(data, ray.next_vert_x - (ray.point_left ? 1 : 0), ray.next_vert_y) == -1 || (ray.next_vert_y < 0 && is_wall(data, ray.next_vert_x - (ray.point_left ? 1 : 0), ray.next_vert_y) == 1) )
			return (0);
		else
		{
			ray.next_vert_x += ray.x_step;
			ray.next_vert_y += ray.y_step;
		}
	}
	return (0);
}

int		ray_horz_hit_sprite(t_ray ray, t_data *data)
{
	ray.found_horz_hit_sprite = 0;
	ray.y_intercept = (int)(data->player.y / TILE_SIZE) * TILE_SIZE;
	ray.y_intercept += (ray.point_down) ? TILE_SIZE : 0;
	ray.x_intercept = data->player.x + (ray.y_intercept - data->player.y) / tan(ray.angel);
	ray.y_step = TILE_SIZE;
	ray.y_step *= (ray.point_up) ? -1 : 1;
	ray.x_step = TILE_SIZE / tan(ray.angel);
	ray.x_step *= (ray.point_right && ray.x_step < 0) ? -1 : 1;
	ray.x_step *= (ray.point_left && ray.x_step > 0) ? -1 : 1;
	ray.next_horz_x = ray.x_intercept;
	ray.next_horz_y = ray.y_intercept;
	ray.horz_wall_hit_x = 0;
	ray.horz_wall_hit_y = 0;
	while (ray.found_horz_hit_sprite == 0)
	{
		if ((is_sprite(data, ray.next_horz_x, ray.next_horz_y - (ray.point_up ? 1 : 0))) == 1 && (is_wall(data, ray.next_horz_x, ray.next_horz_y - (ray.point_up ? 1 : 0)) != 1))
		{
			ray.horz_wall_hit_x = ray.next_horz_x;
			ray.horz_wall_hit_y = ray.next_horz_y;
			ray.found_horz_hit_sprite = 1;
			return (1);
		}
		else if ((is_sprite(data, ray.next_horz_x, ray.next_horz_y - (ray.point_up ? 1 : 0)) == -1) || (is_wall(data, ray.next_horz_x, ray.next_horz_y - (ray.point_up ? 1 : 0)) == 1))
			return (0);
		else
		{
			ray.next_horz_x += ray.x_step;
			ray.next_horz_y += ray.y_step;
		}	
	}
	return (0);
}

void	ray_vert_hit_wall(t_ray *ray, t_data *data)
{
	ray->found_vert_wall_hit = 0;
	ray->x_intercept = (int)(data->player.x / TILE_SIZE) * TILE_SIZE;
	ray->x_intercept += (ray->point_right) ? TILE_SIZE : 0;
	ray->y_intercept = data->player.y + (ray->x_intercept - data->player.x) * tan(ray->angel);
	ray->x_step = TILE_SIZE;
	ray->x_step *= (ray->point_left) ? -1 : 1;
	ray->y_step = TILE_SIZE * tan(ray->angel);
	ray->y_step *= (ray->point_up && ray->y_step > 0) ? -1 : 1;
	ray->y_step *= (ray->point_down && ray->y_step < 0) ? -1 : 1;
	ray->next_vert_x = ray->x_intercept;
	ray->next_vert_y = ray->y_intercept;
	ray->vert_wall_hit_x = 0;
	ray->vert_wall_hit_y = 0;
	while (ray->found_vert_wall_hit == 0)
	{
		if (ray->next_vert_y > 0 && is_wall(data, ray->next_vert_x - (ray->point_left ? 1 : 0), ray->next_vert_y) == 1)
		{
			ray->vert_wall_hit_x = ray->next_vert_x;
			ray->vert_wall_hit_y = ray->next_vert_y;
			ray->found_vert_wall_hit = 1;
			break;
		}
		else if (is_wall(data, ray->next_vert_x - (ray->point_left ? 1 : 0), ray->next_vert_y) == -1)
			break;
		else
		{
			ray->next_vert_x += ray->x_step;
			ray->next_vert_y += ray->y_step;
		}
	}
}

void	ray_horz_hit_wall(t_ray *ray, t_data *data)
{
	ray->found_horz_wall_hit = 0;
	ray->y_intercept = (int)(data->player.y / TILE_SIZE) * TILE_SIZE;
	ray->y_intercept += (ray->point_down) ? TILE_SIZE : 0;
	ray->x_intercept = data->player.x + (ray->y_intercept - data->player.y) / tan(ray->angel);
	ray->y_step = TILE_SIZE;
	ray->y_step *= (ray->point_up) ? -1 : 1;
	ray->x_step = TILE_SIZE / tan(ray->angel);
	ray->x_step *= (ray->point_right && ray->x_step < 0) ? -1 : 1;
	ray->x_step *= (ray->point_left && ray->x_step > 0) ? -1 : 1;
	ray->next_horz_x = ray->x_intercept;
	ray->next_horz_y = ray->y_intercept;
	ray->horz_wall_hit_x = 0;
	ray->horz_wall_hit_y = 0;
	while (ray->found_horz_wall_hit == 0)
	{
		if (is_wall(data, ray->next_horz_x, ray->next_horz_y - (ray->point_up ? 1 : 0)) == 1)
		{
			ray->horz_wall_hit_x = ray->next_horz_x;
			ray->horz_wall_hit_y = ray->next_horz_y;
			ray->found_horz_wall_hit = 1;
			break;
		}
		else if (is_wall(data, ray->next_horz_x, ray->next_horz_y - (ray->point_up ? 1 : 0)) == -1)
			break;
		else
		{
			ray->next_horz_x += ray->x_step;
			ray->next_horz_y += ray->y_step;
		}	
	}
}

void	render_rays(t_data *data)
{
	t_ray *ray;
	double i;
	int column_id;
	int num_rays;
	float angel;
	double horz_distance;
	double vert_distance;

	column_id = 0;
	angel = data->player.rotation_angel - (FOV_ANGLE / 2);
	num_rays = data->conf.win_w / STRIP_WIDTH;
	if (data->rays)
		free_rays_array(data);
	if (!(data->rays = (t_ray **)malloc(sizeof(t_ray *) * num_rays)))
		exit(EXIT_FAILURE);
	while(column_id < num_rays)
	{
		i = 0;
		if(!(ray = (t_ray *)malloc(sizeof(t_ray))))
			exit(EXIT_FAILURE);
		ray->angel = normalize_angle(angel);
		ray_pointer(ray);
		if (ray->angel != 0 || ray->angel != M_PI)
		{
			ray_horz_hit_wall(ray, data);
			ray->found_horz_hit_sprite = ray_horz_hit_sprite(*ray, data);
		}
		if (ray->angel != (M_PI / 2) || ray->angel != (3 * M_PI / 2))
		{
			ray_vert_hit_wall(ray, data);
			ray->found_vert_hit_sprite = ray_vert_hit_sprite(*ray, data);
		}
		horz_distance = (ray->found_horz_wall_hit) ? calculate_distance(data->player.x, data->player.y, ray->horz_wall_hit_x, ray->horz_wall_hit_y) : INFINITY;
		vert_distance = (ray->found_vert_wall_hit) ? calculate_distance(data->player.x, data->player.y, ray->vert_wall_hit_x, ray->vert_wall_hit_y) : INFINITY;
		ray->wall_hit_x = (horz_distance < vert_distance) ? ray->horz_wall_hit_x : ray->vert_wall_hit_x;
		ray->wall_hit_y = (horz_distance < vert_distance) ? ray->horz_wall_hit_y : ray->vert_wall_hit_y;
		ray->distance = (horz_distance < vert_distance) ? horz_distance : vert_distance;
		ray->ray_hit_vertical_wall = (horz_distance > vert_distance) ? 1 : 0;
		line(data,data->player.x * data->conf.map_size, data->player.y * data->conf.map_size, ray->wall_hit_x * data->conf.map_size, ray->wall_hit_y * data->conf.map_size, 0xFFFF00);
		data->rays[column_id] = ray;
		angel += FOV_ANGLE / num_rays;
		column_id++;
	}
	data->conf.num_rays = num_rays;
}

int		wall_color(t_ray *ray)
{
	if (ray->ray_hit_vertical_wall)
		return (0xFFFFFF);
	else
		return (0xCCCCCC);
	return(0);
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

t_img	scale_textures(t_data *data, t_img tex, double scale, int tex_x)
{
	t_img sc_tex;
	int y1;
	double y2;

	sc_tex.height = tex.height * scale;
	sc_tex.width = STRIP_WIDTH;
	sc_tex.img_ptr = mlx_new_image(data->mlx, sc_tex.width, sc_tex.height);
	sc_tex.img_addr = mlx_get_data_addr(sc_tex.img_ptr, &sc_tex.bits_per_pixel, &sc_tex.line_length, &sc_tex.endian);
	y1 = 0;
	y2 = 0;
	while (y1 < sc_tex.height)
	{
		*(unsigned int*)(sc_tex.img_addr + y1 * sc_tex.line_length + 0 * (sc_tex.bits_per_pixel / 8)) = *(unsigned int*)(tex.img_addr + (int)y2 * tex.line_length + tex_x * (tex.bits_per_pixel / 8));
		y1 += 1;
		y2 += 1 / scale;
	}
	return (sc_tex);
}

t_img	choose_texture(t_data *data, t_ray *ray)
{
	if (ray->ray_hit_vertical_wall)
	{
		if (ray->angel > M_PI / 2 && ray->angel <= 3 * M_PI / 2)
			return(data->tex[3]);
		else
			return(data->tex[1]);
	}
	else
	{
		if (ray->angel > 0 && ray->angel <= M_PI)
			return(data->tex[2]);
		else
			return(data->tex[0]);
	}
	
	
}

void	texture_walls(t_data *data, t_ray *ray, int column_id, double scale, int projected_wall_heigth)
{
	t_img	tex;
	int tex_x;
	int tex_y;
	char *c;
	char *a;

	tex_y = 0;
	scale += (scale <= 0) ? 1 : 0;
	if (ray->ray_hit_vertical_wall == 1)
		tex_x = (int)(ray->wall_hit_y) % data->tex[0].width;
	else if (ray->ray_hit_vertical_wall != 1)
		tex_x = (int)(ray->wall_hit_x) % data->tex[0].width;
	tex = scale_textures(data, choose_texture(data, ray), scale, tex_x);
	while (tex_y < tex.height)
	{
		c = data->img.img_addr + ((tex_y + (data->conf.win_h / 2 - projected_wall_heigth / 2)) * data->img.line_length + column_id * (data->img.bits_per_pixel / 8));
		a = tex.img_addr + tex_y * tex.line_length + 0 * (tex.bits_per_pixel / 8);
		*(unsigned int*)c = *(unsigned int*)a;
		tex_y++;
	}
}

void	render_walls(t_data *data)
{
	double projected_wall_heigth;
	double distance_from_player_to_projection;
	double distance_from_player_to_wall;
	int column_id;
	double scale;

	column_id = 0;
	distance_from_player_to_projection = data->conf.win_w / 2 * tanl(FOV_ANGLE / 2);
	while(column_id < data->conf.num_rays)
	{
		distance_from_player_to_wall = (data->rays[column_id]->distance) * cos(data->rays[column_id]->angel - data->player.rotation_angel);
		projected_wall_heigth = (TILE_SIZE * distance_from_player_to_projection) / distance_from_player_to_wall;
		scale = distance_from_player_to_projection / distance_from_player_to_wall;
		texture_walls(data, data->rays[column_id], column_id, scale, projected_wall_heigth);
		column_id++;
	}
}

void	render_ceilling_floor(t_data *data)
{
	rect(data, 0, 0, data->conf.win_w, data->conf.win_h, data->conf.ceill_color);
	rect(data, 0, data->conf.win_h / 2, data->conf.win_w, data->conf.win_h, data->conf.floor_color);
}

int		is_sprite(t_data *data, double x, double y)
{
	int map_index_x;
	int map_index_y;

	map_index_x = (int)(x / TILE_SIZE);
	map_index_y = (int)(y / TILE_SIZE);
	if (map_index_x < 0 || map_index_x > data->conf.win_w || map_index_y < 0 || map_index_y > data->conf.win_h || map_index_y >= data->conf.map_h)
			return (-1);
	if (ft_strlen(data->conf.world_map[map_index_y]) > map_index_x)
		return (data->conf.world_map[map_index_y][map_index_x] == '2' ? 1 : 0);
	return (-1);
}

void	sprites_list(t_data *data)
{
	int i;
	int j;
	t_sprite *tmp;

	i = 0;
	j = 0;
	tmp = (t_sprite *)malloc(sizeof(t_sprite));
	data->sprite = tmp;
	while (j < data->conf.map_h)
	{
		i = 0;
		while (i < ft_strlen(data->conf.world_map[j]))
		{
			if (data->conf.world_map[j][i] == '2')
			{
				tmp->x = (i + 1) * TILE_SIZE;
				tmp->y = (j + 1) * TILE_SIZE;
				tmp->next = (t_sprite *)malloc(sizeof(t_sprite));
				tmp = tmp->next;
			}
			i++;
		}
		j++;
	}
	tmp->next = NULL;
}
void	sprites_distance(t_data *data)
{
	int x;
	int y;
	double angel;
	double a;
	t_sprite *tmp;

	tmp = data->sprite;
	a = atan((tmp->y - data->player.y) / (tmp->x - data->player.x));
	angel = M_PI_2;
	x = data->tex[4].width * cos(a);
	y = data->tex[4].width * sin(a);
	while (tmp != NULL)
	{
		tmp->x1 = tmp->x + (x * cos(angel) - y * sin(angel));
		tmp->y1 = tmp->y + (x * sin(angel) + y * cos(angel));
		tmp->x2 = tmp->x + (x * cos(angel) + y * sin(angel));
		tmp->y2 = tmp->y + (-1 * x * sin(angel) + y * cos(angel));
		tmp->distance = calculate_distance(data->player.x, data->player.y, tmp->x, tmp->y);
//		line(data, tmp->x * data->conf.map_size, tmp->y * data->conf.map_size, tmp->x1 * data->conf.map_size, tmp->y1 * data->conf.map_size, 0x00FF00);
//		line(data, tmp->x * data->conf.map_size, tmp->y * data->conf.map_size, tmp->x2 * data->conf.map_size, tmp->y2 * data->conf.map_size, 0x00FF00);
//		line(data, data->player.x * data->conf.map_size, data->player.y * data->conf.map_size, tmp->x * data->conf.map_size, tmp->y * data->conf.map_size, 0xFF0000);
		tmp = tmp->next;
	}
}

int		point_in_segment(t_data * data, t_ray *ray, t_sprite *sprite)
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
	if (sprite->x1 == sprite->x2)
		if (((ray->wall_hit_y - data->player.y) / (ray->wall_hit_x - data->player.x)) >= ((ft_min(sprite->y1, sprite->y2) - data->player.y) / sprite->distance)
		&& ((ray->wall_hit_y - data->player.y) / (ray->wall_hit_x - data->player.x)) <= ((ft_max(sprite->y1, sprite->y2) - data->player.y) / sprite->distance)
		&& x >= ft_min(data->player.x, ray->wall_hit_x) && x <= ft_max(data->player.x, ray->wall_hit_x))
			{
//				ray->hit_sprite = sqrt(x * x + y * y);
//				circle(data, x * data->conf.map_size, y * data->conf.map_size, 5 * data->conf.map_size, 0x00FF00);
				return (1);
			}
	if (sprite->y1 == sprite->y2)
		if (((ray->wall_hit_x - data->player.x) / (ray->wall_hit_y - data->player.y)) >= ((ft_min(sprite->x1, sprite->x2) - data->player.x) / sprite->distance)
		&& (((ray->wall_hit_x - data->player.x) / (ray->wall_hit_y - data->player.y)) >= ((ft_max(sprite->x1, sprite->x2) - data->player.x) / sprite->distance)
		|| ((ray->wall_hit_x - data->player.x) / (ray->wall_hit_y - data->player.y)) <= ((ft_max(sprite->x1, sprite->x2) - data->player.x) / sprite->distance))
		&& y >= ft_min(data->player.y, ray->wall_hit_y) && y <= ft_max(data->player.y, ray->wall_hit_y))
			{
//				circle(data, x * data->conf.map_size, y * data->conf.map_size, 5 * data->conf.map_size, 0x00FF00);
//				ray->hit_sprite = sqrt(x * x + y * y);
				return (1);
			}
	while ((int)y < ft_max(sprite->y1, sprite->y2))
	{
		x = ft_min(sprite->x1, sprite->x2);
		while ((int)x < ft_max(sprite->x1, sprite->x2))
		{
			if ((int)abs(ray->wall_hit_y - y) == (int)(slope * abs(ray->wall_hit_x - x))
			&& (int)abs(sprite->y1 - y) <= (int)(slope_2 * abs(sprite->x1 - x))
			&& x >= ft_min(data->player.x, ray->wall_hit_x) && x <= ft_max(data->player.x, ray->wall_hit_x)
			&& y >= ft_min(data->player.y, ray->wall_hit_y) && y <= ft_max(data->player.y, ray->wall_hit_y))
			{
				circle(data, x * data->conf.map_size, y * data->conf.map_size, 5 * data->conf.map_size, 0x00FF00);
				ray->hit_sprite = sqrt(x * x + y * y);
				return (1);
			}
			x += 1;
		}
		y += 1;
	}
	return (0);
}

t_img	scale_sprites(t_data *data, t_img tex, double scale, int tex_x)
{
	t_img sc_tex;
	int y1;
	double y2;

	sc_tex.height = tex.height * scale;
	sc_tex.width = STRIP_WIDTH;
	sc_tex.img_ptr = mlx_new_image(data->mlx, sc_tex.width, sc_tex.height);
	sc_tex.img_addr = mlx_get_data_addr(sc_tex.img_ptr, &sc_tex.bits_per_pixel, &sc_tex.line_length, &sc_tex.endian);
	y1 = 0;
	y2 = 0;
	while (y1 < sc_tex.height)
	{
		*(unsigned int*)(sc_tex.img_addr + y1 * sc_tex.line_length + 0 * (sc_tex.bits_per_pixel / 8)) = *(unsigned int*)(tex.img_addr + (int)y2 * tex.line_length + tex_x * (tex.bits_per_pixel / 8));
		y1 += 1;
		y2 += 1 / scale;
	}
	return (sc_tex);
}

void	put_sprite(t_data *data, t_sprite *sprite, t_ray *ray, int column_id, double scale, int projected_sprite_heigth)
{
	t_img	tex;
	int sprite_width;
	double tex_x;
	int tex_y;
	char *c;
	char *a;
	static int j = 0;

	tex_y = 0;
	sprite_width = calculate_distance(sprite->x1, sprite->y1, sprite->x2, sprite->y2);
	scale += (scale <= 0) ? 1 : 0;

	tex_x = (int)ray->hit_sprite % data->tex[4].width;
//	tex_x = column_id % sprite_width;
//	tex_x = column_id % sprite_width % data->tex[4].width;
//	tex_x = tex_x / (double)(sprite_width / data->tex[4].width);
//	printf("#%i# %f - %f - %i\n", sprite_width, tex_x , ray->hit_sprite, data->tex[4].width);
//	tex = scale_sprites(data, data->tex[4], scale, (int)((double)j / ((sprite_width) / (data->tex[4].width))));
	tex = scale_sprites(data, data->tex[4], scale, tex_x);
	while (tex_y < tex.height)
	{
		c = data->img.img_addr + ((tex_y + (data->conf.win_h / 2 - projected_sprite_heigth / 2)) * data->img.line_length + column_id * (data->img.bits_per_pixel / 8));
		a = tex.img_addr + tex_y * tex.line_length + 0 * (tex.bits_per_pixel / 8);
		if (*(unsigned int*)a > 0)
			*(unsigned int*)c = *(unsigned int*)a;
		tex_y++;
	}
	j = j % sprite_width;
	printf("#%i# \n", (int)((double)j / ((double)(sprite_width) / (data->tex[4].width))));
	j++;
}


void	render_sprites(t_data *data)
{
	int column_id;
	double distance_from_player_to_projection;
	double projected_sprite_heigth;
	double scale;
	t_sprite *tmp;

	column_id = 0;
	tmp = data->sprite;
	distance_from_player_to_projection = data->conf.win_w / 2 * tanl(FOV_ANGLE / 2);
	sprites_distance(data);
	line(data, tmp->x * data->conf.map_size, tmp->y * data->conf.map_size, tmp->x1 * data->conf.map_size, tmp->y1 * data->conf.map_size, 0x0000FF);
	line(data, tmp->x * data->conf.map_size, tmp->y * data->conf.map_size, tmp->x2 * data->conf.map_size, tmp->y2 * data->conf.map_size, 0x0000FF);
	line(data, data->player.x * data->conf.map_size, data->player.y * data->conf.map_size, tmp->x * data->conf.map_size, tmp->y * data->conf.map_size, 0x0000FF);
	while(column_id < data->conf.num_rays)
	{
		scale = distance_from_player_to_projection / tmp->distance;
		projected_sprite_heigth = (data->tex[4].height * distance_from_player_to_projection) / tmp->distance;
//		if ((int)abs(data->rays[column_id]->wall_hit_y - tmp->y) == (int)abs(data->rays[column_id]->wall_hit_x - tmp->x))
		if (point_in_segment(data, data->rays[column_id], tmp))
//		if (data->rays[column_id]->found_horz_hit_sprite == 1 || data->rays[column_id]->found_vert_hit_sprite == 1)
		{
			
//			rect(data, tmp->x * data->conf.map_size, tmp->y * data->conf.map_size, data->tex[4].width * data->conf.map_size, data->tex[4].height * data->conf.map_size, 0x0000FF);
			line(data,data->player.x * data->conf.map_size, data->player.y * data->conf.map_size, data->rays[column_id]->wall_hit_x * data->conf.map_size, data->rays[column_id]->wall_hit_y * data->conf.map_size, 0xFF0000);
			put_sprite(data, tmp, data->rays[column_id], column_id, scale, projected_sprite_heigth);
		}
//		line(data, tmp->x * data->conf.map_size, tmp->y * data->conf.map_size, tmp->x1 * data->conf.map_size, tmp->y1 * data->conf.map_size, 0x0000FF);
//		line(data, tmp->x * data->conf.map_size, tmp->y * data->conf.map_size, tmp->x2 * data->conf.map_size, tmp->y2 * data->conf.map_size, 0x0000FF);
//		line(data, data->player.x * data->conf.map_size, data->player.y * data->conf.map_size, tmp->x * data->conf.map_size, tmp->y * data->conf.map_size, 0x0000FF);

		column_id++;
	}
}


void	mlx_close(t_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	exit(EXIT_SUCCESS);
}

void	move(int keycode, t_data *data)
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

void	update(int keycode, t_data *data)
{
	t_img	put_img;

	move(keycode, data);
	render_ceilling_floor(data);
	render_map(data);
	render_rays(data);
	render_player(data);
	render_walls(data);
	render_sprites(data);
	put_img = data->img;
	mlx_put_image_to_window(data->mlx, data->mlx_win, put_img.img_ptr, 0, 0);
}

int	main(int argc, char **argv)
{
	int fd;
	size_t	elm_count;
	t_data	data;
	t_list	*list;

	start(&data);
//Working with the input file
	fd = open(argv[1], O_RDONLY);
	check_error_save(&data, argc, argv, fd);
	elm_count = make_list(fd, &list);
	data.conf.str_num = elm_count;
//	data.conf.map_h = elm_count;
	data.str = getinfo(&list, elm_count);
//	printf("%f|%f", data.player.x, data.player.y);
//	printf("|%s|\n", data.str[0]);
	get_resolution(data.str, &data, elm_count);
//	printf("<%d><%d>", data.conf.win_w, data.conf.win_h);
	data.conf.map_h = get_map(data.str, &data);
	check_map(&data);
	sprites_list(&data);
	get_player_location(&data);
//	printf("%d\n", data.conf.map_h);
//	for(int z = 0; z < data.conf.map_h; z++)
//		printf("%s\n", data.conf.world_map[z]);
//	printf("%i, %i\n", data.img.width, data.img.height);
//	printf("%s", data.conf.world_map);
//Working with the graphics
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, data.conf.win_w, data.conf.win_h, "Cub3D");
	data.img.img_ptr = mlx_new_image(data.mlx, data.conf.win_w, data.conf.win_h);
	data.img.img_addr = mlx_get_data_addr(data.img.img_ptr, &data.img.bits_per_pixel, &data.img.line_length, &data.img.endian);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img.img_ptr, 0, 0);
	get_textpath(data.str, &data, elm_count);
	get_textures(&data);
	get_floor_ceilling(data.str, &data, elm_count);
//	mlx_pixel_put(data.mlx, data.mlx_win, 111, 111, 0xFFFFFFFF);
//	rect(&data, 2, 2, TILE_SIZE, TILE_SIZE, 0x00FF00);
//	line(&data, 1, 1, 8, 8, 0x00FFA0);
//	line(&data, 1, 5, 8, 8, 0x00FFB0);
/*	int i;
	int j;
	j = -1 * 50;
	while(j <= 50)
	{
		i = -1 * 50;
		while (i <= 50)
		{
			if (i * i <= 50 * 50 - j * j)
				line(&data, 300, 200, i + 300, j + 200, 0x00FFC0);
			i++;
		}
		j++;
	}*/
//	line(&data, 2, 200, 300, 2, 0x00FFC0);
//	line(&data, 1, 1, 8, 1, 0x00FFD0);
//	line(&data, 1, 1, 1, 8, 0x00FFE0);

//	render_map(&data);
	mlx_hook(data.mlx_win, 2, 1L<<0, update, &data);
//	mlx_clear_window(data.mlx, data.mlx_win);
	mlx_loop(data.mlx);
	return (0);
}