#include "cub3d.h"


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
	// Working with graphics
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, W, H, "Cub3D");
	mlx_loop(data.mlx);
	return (0);
}
