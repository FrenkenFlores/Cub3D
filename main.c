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

void	ft_rect(t_data *data, double x, double y, int rect_width, int rect_height, int color)
{
	int i;
	int j;

	j = 0;
	while(j <= rect_height)
	{
		i = 0;
		while (i <= rect_width)
		{
			mlx_pixel_put(data->mlx, data->mlx_win, TILE_SIZE * x + i, TILE_SIZE * y + j, color);
			i++;
		}
		j++;
	}
}

void	ft_circle(t_data *data, double x, double y, double radius, int color)
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
				mlx_pixel_put(data->mlx, data->mlx_win, TILE_SIZE * x + i, TILE_SIZE * y + j, color);
			i++;
		}
		j++;
	}
}
/*
void	ft_line(t_data *data, double x1, double y1, double x2, double y2, int color)
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
void	ft_line(t_data *data, double x1, double y1, double x2, double y2, int color)
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

void	ft_check_error_save(t_data *data, int argc, char **argv, int fd)
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

t_list	*ft_push_back(char *str, t_list *old_list)
{
	t_list	*new_list;

	if (!(new_list = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	new_list->content = str;
	new_list->next = old_list;
	return (new_list);
}

size_t	ft_make_list(int fd, t_list **list)
{
	char	*str;
	size_t	i;

	i = 0;
	*list = NULL;
	while(get_next_line(fd, &str))
	{
		*list = ft_push_back(str, *list);
		i++;
	}
	*list = ft_push_back(str, *list);
	i++;
	return (i);
}

void	ft_start(t_data *data)
{
	data->player.x = -1;
	data->player.y = -1;
	data->player.turn_direction = 0;
	data->conf.map_h = -1;
	data->conf.map_w = -1;
	data->conf.win_h = 0;
	data->conf.win_w = 0;
	data->conf.world_map = NULL;
	data->conf.floor_color = -1;
	data->conf.cell_color = -1;
	data->sprite = NULL;
	data->save = 0;
}

int		ft_get_map(char **ptr, t_data *data, size_t elm_count)
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

void	ft_check_map_error(char **ptr, size_t map_loc, size_t elm_count)
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

void	ft_getR(char **str, t_data *data, size_t elm_count)
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


char	**ft_getinfo(t_list **list, size_t elm_count)
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
/*
void	ft_draw_map(t_data *data)
{
	int i = 0;
	int j = 0;
	double x = 0;
	double y = 0;
	t_player plr = data->player;
	while (data->str[j])
	{
		i = 0;
		while (data->str[j][i])
		{
			if (data->str[j][i] == '1')
			{
				y = j * 20;
				while (y / (j * 20 + 20) != 1)
				{
					x = i * 20;
					while (x / (i * 20 + 20) != 1)
					{
						mlx_pixel_put(data->mlx, data->mlx_win, x, y, 0xFFFFFF);
						x++;
					}
					y++;
				}
			}
			if (data->str[j][i] == 'P')
			{
				plr.turn_direction -= PI / 8;
				while (plr.turn_direction <= data->player.turn_direction + PI / 8)
				{
					plr.x = i * 20 + data->player.x;
					plr.y = j * 20 + data->player.y;
					while (data->str[(int)(plr.y) / 20][(int)(plr.x) / 20] != '1')
					{
						plr.x += cos(plr.turn_direction);
						plr.y += sin(plr.turn_direction);
						mlx_pixel_put(data->mlx, data->mlx_win, plr.x, plr.y, 0x22CCFF);
					}
					double w1 = 180 * atan(plr.y / plr.x) / PI;
					double w2 = 180 * atan((j * 20 + plr.y - data->player.y) / (i * 20 + plr.x - data->player.x)) / PI;
					double w3 = 90 - w2;
					double l = sqrt(pow((i * 20 + data->player.x - plr.x), 2) + pow((j * 20 + data->player.y - plr.y), 2));
					double wall = 0;
					while (wall < 5000 / l)
					{
//						if (w2 < 0)
//							w2 += 2 * PI;
						mlx_pixel_put(data->mlx, data->mlx_win, 20 * l * sin((w2 * PI / 180) - plr.turn_direction), 350 + wall, 0xAAFFAA); // l * cos(w3 * PI / 180)
						wall += 1;
					}
					plr.turn_direction += 0.001;
				}
			}
			i++;
		}
		j++;
	}
}
*/

void	ft_draw_map(t_data *data)
{
	int i = 0;
	int j = 0;
	while (data->str[j])
	{
		i = 0;
		while (data->str[j][i])
		{
			if (data->str[j][i] == '1')
				ft_rect(data, i, j, TILE_SIZE, TILE_SIZE, 0xFFFFFF);
			else if (data->str[j][i] == '0')
				ft_rect(data, i, j, TILE_SIZE, TILE_SIZE, 0x00FF00);
			else if (data->str[j][i] == 'P')
				ft_circle(data, i, j, 16, 0xFF88FF);
			i++;
		}
		j++;
	}
}

void	ft_move(int keycode, t_data *data)
{
	if (keycode == 13)
	{
		data->player.y += sin(data->player.turn_direction) * 4;
		data->player.x += cos(data->player.turn_direction) * 4;
	}
	if (keycode == 1)
	{
		data->player.y -= sin(data->player.turn_direction) * 4;
		data->player.x -= cos(data->player.turn_direction) * 4;
	}
	if (keycode == 0)
		data->player.turn_direction -= 0.1;
	if (keycode == 2)
		data->player.turn_direction += 0.1;
	if (keycode == 53)
		mlx_destroy_window(data->mlx, data->mlx_win);
}

void	ft_update(int keycode, t_data *data)
{
//	mlx_clear_window(data->mlx, data->mlx_win);
//	ft_move(keycode, data);
	ft_draw_map(data);
}




int	main(int argc, char **argv)
{
	int fd;
	size_t	elm_count;
	t_data	data;
	t_list	*list;

	ft_start(&data);
//Working with the input file
	fd = open(argv[1], O_RDONLY);
	ft_check_error_save(&data, argc, argv, fd);
	elm_count = ft_make_list(fd, &list);
	data.str = ft_getinfo(&list, elm_count);
//	ft_getR(data.str, &data, elm_count);
//	ft_get_map(data.str, &data, elm_count);
//	printf("%i, %i\n", data.img.width, data.img.height);
//	printf("%s", data.conf.world_map);
//Working with the graphics
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, 1200, 900, "Cub3D");
//	mlx_pixel_put(data.mlx, data.mlx_win, 111, 111, 0xFFFFFFFF);
//	ft_rect(&data, 2, 2, TILE_SIZE, TILE_SIZE, 0x00FF00);
//	ft_line(&data, 1, 1, 8, 8, 0x00FFA0);
//	ft_line(&data, 1, 5, 8, 8, 0x00FFB0);
	ft_line(&data, 50, 10, 380, 180, 0x00FFC0);
//	ft_line(&data, 1, 1, 8, 1, 0x00FFD0);
//	ft_line(&data, 1, 1, 1, 8, 0x00FFE0);

//	ft_draw_map(&data);
//	mlx_hook(data.mlx_win, 2, 1L<<0, ft_update, &data);
	mlx_loop(data.mlx);
	return (0);
}
