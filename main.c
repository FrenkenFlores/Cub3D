#include "cub3d.h"


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

double normalize_angle(double angle)
{
	while (angle > 2 * PI)
		angle = angle - 2 * PI;
	while (angle < 0)
		angle = angle + (2 * PI);
	return (angle);
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
			mlx_pixel_put(data->mlx, data->mlx_win, x + i, y + j, color);
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
				mlx_pixel_put(data->mlx, data->mlx_win, x + i, y + j, color);
			i++;
		}
		j++;
	}
}
/*
void	line(t_data *data, double x1, double y1, double x2, double y2, int color)
{
	double i;
	double j;

	j = y1;
	while (j <= abs(y2 - y1) * TILE_SIZE)
	{
		i = x1;
		while (i <= abs(x2 - x1) * TILE_SIZE)
		{
			if (abs(y2 - y1) != 0 && i == ((j - y1) * (x2 - x1) / (y2 - y1)) + x1)
				mlx_pixel_put(data->mlx, data->mlx_win, TILE_SIZE * x1 + i, TILE_SIZE * y1 + j, color);
			if (abs(x2 - x1) != 0 && j == ((i - x1) * (y2 - y1) / (x2 - x1)) + y1)
				mlx_pixel_put(data->mlx, data->mlx_win, TILE_SIZE * x1 + i, TILE_SIZE * y1 + j, color);
			i++;
		}
		j++;
	}
}
*/
void	line(t_data *data, double x1, double y1, double x2, double y2, int color)
{
	double i;
	double j;
	double alpha;

	alpha = (y2 - y1) / (x2 - x1);
	j = 0;
	while (j <= abs(y2 - y1))
	{
		i = 0;
		while (i <= abs(x2 - x1))
		{
			if (j >= alpha * i - 0.5 && j <= alpha * i + 0.5)
				mlx_pixel_put(data->mlx, data->mlx_win, x1 + i, y1 + j, color);
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
	if (x < 0 || x > data->conf.win_w || y < 0 || y > data->conf.win_h)
			return (0);
	return (data->str[map_index_y][map_index_x] == '1' ? 1 : 0);
}


void	check_error_save(t_data *data, int argc, char **argv, int fd)
{
	if (argc < 2)
	{
		errno = EINVAL;
		perror("Error\n");
		write(2,"\nToo few arguments\n", 19);
		exit(-1);
	}
	if (argc > 2 && ((ft_strncmp(argv[2],"--save", ft_strlen("--save")) != 0) || (ft_strlen(argv[2]) != ft_strlen("--save"))))
	{
		errno = EINVAL;
		perror("Error\n");
		write(2, "\nOnly --save flag is allowed\n", 29);
		exit(-1);
	}
	else 
		data->save = 1;
	if (argc >= 2 && (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 2)) != 0)
	{
		errno = EINVAL;
		perror("Error\n");
		write(2, "\nInvalid file\n", 14);
		exit(-1);
	}
	if (fd < 0)
	{
		perror("Error\n");
		exit(-1);
	}
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
	j = 0;
	while (data->str[j])
	{
		i = 0;
		while (data->str[j][i])
		{
			if (data->str[j][i] == 'P')			
				{
					data->player.x = (i + 1) * TILE_SIZE;
					data->player.y = (j + 1) * TILE_SIZE;
					break;
				}
			i++;
		}
		j++;
	}
}


void	start(t_data *data)
{
	data->player.x = -1; //change later
	data->player.y = -1;
	data->player.turn_direction = 0;   // +1 : right, -1 : left
	data->player.walk_directoin = 0;  // +1 : forward, -1 : backward
	data->player.radius = 16;
	data->player.rotation_angel = PI / 2;
	data->player.move_speed = 8.0;
	data->player.rotation_speed = 15 * (PI / 180);
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
	data->conf.win_h = 960;
	data->conf.win_w = 1200;
	data->conf.world_map = NULL;
	data->conf.floor_color = -1;
	data->conf.cell_color = -1;
	data->sprite = NULL;
	data->save = 0;
}

int		get_map(char **ptr, t_data *data, size_t elm_count)
{
	size_t i;
	size_t j;
	size_t z;
	size_t k;
	size_t length;

	length = 0;
	i = elm_count - 1;
	j = 0;
	z = 0;
	k = 0;
	printf("<<i = %i, %c>>\n",i ,  ptr[i - 1][0]);
	while (ptr[i] && i > 0)
	{
		printf("x1");
		while (ptr[i][j] != '\0' && (ptr[i][j] == '1' || ptr[i][j] == ' ' || ptr[i][j] == '0' || ptr[i][j] == 'N' || ptr[i][j] == 'S' || ptr[i][j] == 'E' || ptr[i][j] == 'W' || ptr[i][j] == 'P' || ptr[i][j] == '2'))
			j++;
		printf("::%i, %i::\n", j, ft_strlen(ptr[i]));
		if (j == ft_strlen(ptr[i]))
		{
			length = length + ft_strlen(ptr[i]) + 1; //+1 for '\n'
			i--;
		}
		else
			break;
	}
	printf("^^^%s^^^", ptr[i]);
	printf("::%i::\n", length);
//	if (!(data->conf.world_map = (char*)malloc(sizeof(char) * length + 1))
//		exit(EXIT_FAILURE); // for '\0;
//	printf("::%i::\n", ft_strlen(data->conf.world_map));
	printf ("8#%i#8\n#", i);
	while (i < elm_count)
	{
		printf ("#%i#%s\n#", i, ptr[i]);
//			printf("%i\n", ptr[i - 1][0] == '1');
//		printf ("elmC = %d, i = %d\n", elm_count, i);
		while (ptr[i][k] != '\0')
			data->conf.world_map[z++] = ptr[i][k++];
		data->conf.world_map[z++] = '\n';
		printf ("%s", ptr[i]);
		i++;
		if (i == elm_count - 1)
			return (1);
		i++;
	}
	errno = EINVAL;   //карта вообще не сущ.
	perror("Error");
	write(2,"\nMap dose not exist\n", 20);
	exit(EXIT_FAILURE);
}

void	check_map_error(char **ptr, size_t map_loc, size_t elm_count)
{
	size_t i;
	size_t j;
	int g = 0;
	char	**map;

	i = 0;
	j = 0;
//	printf("%d", elm_count);
	map = (char**)malloc(sizeof(char*) * elm_count + 1);
	while (i < elm_count)
	{
//		printf("x");
		map[i] = ptr[i];
//		printf("%s\n", ptr[i]);
		i++;
	}
//	printf("%s", map[5]);
	map[i] = NULL;
	while (map[map_loc][j] == ' ')
		j++;
	while (g != 60) // дороботать
	{
		printf ("  <player:%d,%d>  \n",map_loc, j);

		if (map[map_loc][j + 1] == '1')
			map[map_loc][j++] = 'X';
		else if (map[map_loc + 1][j] == '1')
			map[map_loc++][j] = 'X';
		else if (map[map_loc][j - 1] == '1')
			map[map_loc][j--] = 'X';
		else if (map[map_loc - 1][j] == '1')
		{
			map[map_loc--][j] = 'X';
			if (map[map_loc - 1][j] == 'X')
				break;
		}
		/*
		if (map[map_loc][j] == '1')
		{
			map[map_loc][j] = 'X';
			if (map[map_loc][j + 1] == '\0')
			{
				map[map_loc][j] = 'X';
				map_loc++;
				j = -1;
			}
		}
		j++;*/
		g++;
	}
	
//	printf ("%ld", j);
	while (*map != NULL)
		printf("%s\n", *map++);
}

void	getR(char **str, t_data *data, size_t elm_count)
{
	size_t	j;
	size_t i;
	
	i = 0;
	while (j < elm_count)
	{
		i = 0;
		if (str[j][i] == 'R')
		{
			i++;
			while(str[j][i] == ' ')
				i++;
			data->img.width = ft_atoi(str[j] + i);
			i += ft_numsize(data->img.width);
			data->img.height = ft_atoi(str[j] + i);
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
	ptr = (char**)malloc((sizeof(char*) * j) + 1);
	while (tmp && j >= 0)
	{
		ptr[j - 1] = tmp->content;
		tmp = tmp->next;
		j--;
	}
	ptr[elm_count] = NULL;
return (ptr);
}

void	render_map(t_data *data)
{
	int i = 0;
	int j = 0;
	while (data->str[j])
	{
		i = 0;
		while (data->str[j][i])
		{
			if (data->str[j][i] == '1')
				rect(data, i * TILE_SIZE * MAP_SIZE, j * TILE_SIZE * MAP_SIZE, TILE_SIZE * MAP_SIZE, TILE_SIZE * MAP_SIZE, 0xFFFFFF);
			else if (data->str[j][i] == '0')
				rect(data, i * TILE_SIZE * MAP_SIZE, j * TILE_SIZE * MAP_SIZE, TILE_SIZE * MAP_SIZE, TILE_SIZE * MAP_SIZE, 0x000000);
			i++;
		}
		j++;
	}
}

void	render_player(t_data *data)
{	
	circle(data, data->player.x * MAP_SIZE, data->player.y * MAP_SIZE, data->player.radius * MAP_SIZE, 0x212121);
}

void	free_rays_array(t_data *data)
{
	int i;

	i = 0;
	while (i < data->conf.num_rays && data->rays[i])
	{
		free (data->rays[i]);
		i++;
	}
	free (data->rays);
}

void	ray_pointer(t_ray *ray)
{
		ray->point_down = (ray->angel >= 0 && ray->angel <= PI) ? 1 : 0;
		ray->point_up = !ray->point_down;
		ray->point_left = (ray->angel >= PI / 2 && ray->angel <= 3 * PI / 2) ? 1 : 0;
		ray->point_right = !ray->point_left;
}

void	ray_conf(t_ray *ray, t_data *data)
{
	ray->foundHorWallHit = 0;
	ray->foundVertWallHit = 0;
	ray->yintercept = (int)(data->player.y / TILE_SIZE) * TILE_SIZE;
	ray->yintercept += (ray->point_down) ? TILE_SIZE : 0;
	ray->xintercept = data->player.x + (ray->yintercept - data->player.y) / tan(ray->angel);
	ray->ystep = TILE_SIZE;
	ray->ystep *= (ray->point_up) ? -1 : 1;
	ray->xstep = TILE_SIZE / tan(ray->angel);
	ray->xstep *= (ray->point_left && ray->xstep > 0) ? -1 : 1;
	ray->xstep *= (ray->point_right && ray->xstep < 0) ? -1 : 1;
}

void	render_rays(t_data *data)
{
	t_ray *ray;
	int i;
	int column_id;
	int num_rays;
	double angel;

	column_id = 0;
	angel = normalize_angle(data->player.rotation_angel - (FOV_ANGLE / 2));
	num_rays = data->conf.win_w / STRIP_WIDTH;
	if (data->rays)
		free_rays_array(data);
	if (!(data->rays = (t_ray **)malloc(sizeof(t_ray *) * num_rays)))
		exit(EXIT_FAILURE);
	while(column_id < num_rays)
	{
		i = 0;
		ray = (t_ray *)malloc(sizeof(t_ray));

		



		

		while(is_wall(data, data->player.x + i * cos(angel), data->player.y + i * sin(angel)) == 0)
		{
			mlx_pixel_put(data->mlx, data->mlx_win, (data->player.x + i * cos(angel)) * MAP_SIZE, (data->player.y + i * sin(angel)) * MAP_SIZE, 0xDDDDAA);
			i++;
		}

		ray->distance = i;
		ray->angel = normalize_angle(angel);
		ray_pointer(ray);
		data->rays[column_id] = ray;
//		printf("#%i#|angle %f|up %i|down %i|left %i|right %i\n",column_id, data->rays[column_id]->angel, data->rays[column_id]->point_up, data->rays[column_id]->point_down, data->rays[column_id]->point_left, data->rays[column_id]->point_right);
//		printf("ray(%i) : %f\n",column_id, data->rays[column_id]->distance);		// check #1
		angel += FOV_ANGLE / num_rays;
		column_id++;
	}
	data->conf.num_rays = num_rays;
//	printf("ray(%i) : %f\n",15, data->rays[15]->distance);  //check #2
}

void	render_walls(t_data *data)
{
	double projected_wall_heigth;
	double distance_from_player_to_projection;
	double distance_from_player_to_wall;
	int column_id;

	column_id = 0;
	distance_from_player_to_projection = data->conf.win_w / 2 * tan(FOV_ANGLE / 2);
	while(column_id < data->conf.num_rays)
	{
		distance_from_player_to_wall = (data->rays[column_id]->distance);// * cos(data->rays[column_id]->angel - data->player.rotation_angel);
		projected_wall_heigth = (TILE_SIZE * distance_from_player_to_projection) / distance_from_player_to_wall;
		rect(data, column_id * STRIP_WIDTH, data->conf.win_h / 2 - projected_wall_heigth / 2, STRIP_WIDTH, projected_wall_heigth, 0xFFFFFF);
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
	double	player_new_x;
	double	player_new_y;	

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
	if ((is_wall(data, player_new_x, player_new_y)) == 0)
	{
		data->player.y = player_new_y;
		data->player.x = player_new_x;
	}
}

void	update(int keycode, t_data *data)
{
	mlx_clear_window(data->mlx, data->mlx_win);
	move(keycode, data);
	render_map(data);
	render_rays(data);
	render_player(data);
//	render_walls(data);
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
	data.str = getinfo(&list, elm_count);
	get_player_location(&data);
//	printf("%f|%f", data.player.x, data.player.y);
//	getR(data.str, &data, elm_count);
//	get_map(data.str, &data, elm_count);
//	printf("%i, %i\n", data.img.width, data.img.height);
//	printf("%s", data.conf.world_map);
//Working with the graphics
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, data.conf.win_w, data.conf.win_h, "Cub3D");
//	mlx_pixel_put(data.mlx, data.mlx_win, 111, 111, 0xFFFFFFFF);
//	rect(&data, 2, 2, TILE_SIZE, TILE_SIZE, 0x00FF00);
//	line(&data, 1, 1, 8, 8, 0x00FFA0);
//	line(&data, 1, 5, 8, 8, 0x00FFB0);
//	line(&data, 50, 10, 380, 180, 0x00FFC0);
//	line(&data, 1, 1, 8, 1, 0x00FFD0);
//	line(&data, 1, 1, 1, 8, 0x00FFE0);

//	render_map(&data);
	mlx_hook(data.mlx_win, 2, 1L<<0, update, &data);
	mlx_loop(data.mlx);
	return (0);
}
