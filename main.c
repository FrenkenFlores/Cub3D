#include "cub3d.h"

int TILE_SIZE = 54;
int MAP_NUM_ROWS = 11;
int MAP_NUM_COLS = 15;

int WINDOW_WIDTH = MAP_NUM_COLS * TILE_SIZE;
int WINDOW_HEIGHT = MAP_NUM_ROWS * TILE_SIZE;

int FOV_ANGLE = 60 * (PI / 180);
int WALL_STRIP_WIDTH = 10;
int NUM_RAYS = WINDOW_WIDTH / WALL_STRIP_WIDTH;
int MAP_SCALE = 0.2;


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
	data->player.pos.x = -1;
	data->player.pos.y = -1;
	data->player.dir = 0;
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

size_t	ft_get_map_location(char **ptr)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (ptr[i + 1] != NULL && (ptr[i][j] != ' ' || ptr[i][j] != '1'))
	{
		i++;
		if(ptr[i][j] == ' ' || ptr[i][j] == '1')
		{
			while (ptr[i][j] != '0' && (ptr[i][j] == ' ' || ptr[i][j] == '1'))
				j++;
			if (ft_strlen(ptr[i]) == j)
				return (i);
			errno = EINVAL;    //карта не закрыта
			perror("Error");
			write(2,"\nUncorrect map\n", 15);
			exit(-1);
		}
	}
	errno = EINVAL;   //карта вообще не сущ.
	perror("Error");
	write(2,"\nMap dose not exist\n", 20);
	exit(-1);
	return (0);
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

void	ft_get_map_wh(t_list **list, char **ptr, size_t elm_count)
{
	size_t map_loc;

	map_loc = ft_get_map_location(ptr);
//	printf("%d", elm_count);
//	printf("%ld", map_loc);
//	ft_check_map_error(ptr, map_loc, elm_count);
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

void	rect(t_data *data, int x, int y, int width, int height, int color)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(j <= height)
	{
		while (i <= width)
		{
			mlx_pixel_put(data->mlx, data->mlx_win, TILE_SIZE * x + i, TILE_SIZE * y + j, color);
			i++;
		}
		j++;
		
	}
}

void	line(t_data *data, int x1, int y1, int x2, int y2, int color)
{
	int i;
	int j;
	double k;

	i = 0;
	j = 0;
	k = (y2 - y1) / (x2 - x1);
	while((x1 + i != x2) && (y1 + j != y2))
	{
		mlx_pixel_put(data->mlx, data->mlx_win, x + i, k * (x + i), color);

	}
}

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
				rect(data, i, j, TILE_SIZE, TILE_SIZE, 0xFFFFFF);
			else if (data->str[j][i] == '0')
				rect(data, i, j, TILE_SIZE, TILE_SIZE, 0x000000);
			i++;
		}
		j++;
	}
}

void	ft_draw_player(t_data *data)
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
/*			if (data->str[j][i] == 'P')
			{
				plr.dir -= PI / 8;
				while (plr.dir <= data->player.dir + PI / 8)
				{
					plr.pos.x = i * 20 + data->player.pos.x;
					plr.pos.y = j * 20 + data->player.pos.y;
					while (data->str[(int)(plr.pos.y) / 20][(int)(plr.pos.x) / 20] != '1')
					{
						plr.pos.x += cos(plr.dir);
						plr.pos.y += sin(plr.dir);
						mlx_pixel_put(data->mlx, data->mlx_win, plr.pos.x, plr.pos.y, 0x22CCFF);
					}
					double w1 = 180 * atan(plr.pos.y / plr.pos.x) / PI;
					double w2 = 180 * atan((j * 20 + plr.pos.y - data->player.pos.y) / (i * 20 + plr.pos.x - data->player.pos.x)) / PI;
					double w3 = 90 - w2;
					double l = sqrt(pow((i * 20 + data->player.pos.x - plr.pos.x), 2) + pow((j * 20 + data->player.pos.y - plr.pos.y), 2));
					double wall = 0;
					while (wall < 5000 / l)
					{
//						if (w2 < 0)
//							w2 += 2 * PI;
						mlx_pixel_put(data->mlx, data->mlx_win, 20 * l * sin((w2 * PI / 180) - plr.dir), 350 + wall, 0xAAFFAA); // l * cos(w3 * PI / 180)
						wall += 1;
					}
					plr.dir += 0.001;
				}
			}*/
			if (data-> str[j][i] == 'P')
			{
				
			}
			i++;
		}
		j++;
	}
}

void	ft_draw(int keycode, t_data *data)
{
	ft_update(keycode, data);
	ft_draw_map(data);
	ft_draw_player(data);
}


void	ft_update(int keycode, t_data *data)
{
	mlx_clear_window(data->mlx, data->mlx_win);
	if (keycode == 13)
	{
		data->player.pos.y += sin(data->player.dir) * 4;
		data->player.pos.x += cos(data->player.dir) * 4;
	}
	if (keycode == 1)
	{
		data->player.pos.y -= sin(data->player.dir) * 4;
		data->player.pos.x -= cos(data->player.dir) * 4;
	}
	if (keycode == 0)
		data->player.dir -= 0.1;
	if (keycode == 2)
		data->player.dir += 0.1;
	if (keycode == 53)
		mlx_destroy_window(data->mlx, data->mlx_win);
	ft_draw_map(data);
}

int             ft_close(int keycode, t_data *data)
{
	if (keycode == 'w')
    mlx_destroy_window(data->mlx, data->mlx_win);
}

int	main(int argc, char **argv)
{
	int fd;
	size_t	elm_count;	//counts the amout of lines in the input map.cub file
	t_data	data;
	t_list	*list;

	// Working with the input file map.cub
	fd = open(argv[1], O_RDONLY);
	ft_start(&data);	//initializing data values
	ft_check_error_save(&data, argc, argv, fd); //checking for input errors and searching for save flag
	elm_count = ft_make_list(fd, &list);	// makes a list of lines from the input file
	data.str = ft_getinfo(&list, elm_count);	// makes an array of lines frim the list and returns a pointer to that array
	// Working the graphics
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, W, H, "Cub3D");
	ft_draw_map(&data);
	mlx_hook(data.mlx_win, 2, 1L<<0, ft_draw, &data);
	mlx_loop(data.mlx);
	return (0);
}
