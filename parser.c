#include "cub3d.h"

void		ft_put_error(char *s, int id)
{
	if (!s)
		return ;
	errno = id;
	perror("Error ");
	write(2, s, ft_strlen(s));
	exit(EXIT_FAILURE);
}

void	check_error_save(t_data *data, int argc, char **argv, int fd)
{
	if (argc < 2)
		ft_put_error("\nToo few arguments\n", EINVAL);
	if (argc > 2 && ((ft_strncmp(argv[2],"--save", ft_strlen("--save")) != 0) || (ft_strlen(argv[2]) != ft_strlen("--save"))))
		ft_put_error("\nOnly --save flag is allowed\n", EINVAL);
	else if (argc > 2 && ((ft_strncmp(argv[2],"--save", ft_strlen("--save")) == 0) || (ft_strlen(argv[2]) == ft_strlen("--save"))))
		data->save = 1;
	if (argc >= 2 && (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 2)) != 0)
		ft_put_error("\nInvalid file\n", EINVAL);
	if (fd < 0)
		ft_put_error("\nCan not open file\n", EINVAL);
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
int		check_position(char **world_map, int j, int i)
{
	if (world_map[j][i] != '1' && world_map[j][i] != '2' && world_map[j][i] != '0'
	&& world_map[j][i] != 'N' && world_map[j][i] != 'E' && world_map[j][i] != 'S'
	&& world_map[j][i] != 'W')
		return (-1);
	return (1);
}