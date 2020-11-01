#include "cub3d.h"

void	launch(int keycode, t_data *data)
{
	t_img	put_img;

	key_input(keycode, data);
	render_ceilling_floor(data);
	render_map(data);
	render_rays(data);
	render_player(data);
	render_walls(data);
	render_sprites(data);
	put_img = data->img;
	mlx_put_image_to_window(data->mlx, data->mlx_win, put_img.img_ptr, 0, 0);
}

void	ft_bzero(void *str, size_t nbr)
{
	size_t i;

	i = 0;
	while (i < nbr)
	{
		*((char*)str++) = '\0';
		i++;
	}
}

static void		create_bmp_header(t_data *data, int size, int fd)
{
	unsigned char		bmp_header[54];

	ft_bzero(bmp_header, 54);
	bmp_header[0] = (unsigned char)'B';
	bmp_header[1] = (unsigned char)'M';
	bmp_header[2] = (unsigned char)size;
	bmp_header[3] = (unsigned char)(size >> 8);
	bmp_header[4] = (unsigned char)(size >> 16);
	bmp_header[5] = (unsigned char)(size >> 24);
	bmp_header[10] = (unsigned char)54;
	bmp_header[14] = (unsigned char)40;
	bmp_header[18] = (unsigned char)data->conf.win_w;
	bmp_header[19] = (unsigned char)(data->conf.win_w >> 8);
	bmp_header[20] = (unsigned char)(data->conf.win_w >> 16);
	bmp_header[21] = (unsigned char)(data->conf.win_w >> 24);
	bmp_header[22] = (unsigned char)data->conf.win_h;
	bmp_header[23] = (unsigned char)(data->conf.win_h >> 8);
	bmp_header[24] = (unsigned char)(data->conf.win_h >> 16);
	bmp_header[25] = (unsigned char)(data->conf.win_h >> 24);
	bmp_header[26] = (unsigned char)1;
	bmp_header[28] = (unsigned char)24;
	write(fd, bmp_header, 54);
}

static void		print_pixels(t_data *data, int fd)
{
	unsigned int		color;
	int					y;
	int					x;

	y = data->conf.win_h - 1;
	while (y >= 0)
	{
		x = -1;
		while (++x < data->conf.win_w)
		{
			color = *(unsigned int *)(data->img.img_addr
					+ (y * data->img.line_length
					+ x * (data->img.bits_per_pixel / 8)));
			write(fd, &color, 3);
		}
		y--;
	}
}


void	screen_shot(t_data *data)
{
	int fd;
	int size;

	if (data->conf.win_w % 4)
		data->conf.win_w = data->conf.win_w - (data->conf.win_w % 4);
	size = data->conf.win_w * data->conf.win_h + 54;
	if (!(fd = open("./screenshot.bmp", O_RDWR | O_CREAT, 0666)))
		ft_put_error("Faild to screenshot", EXIT_FAILURE);
	create_bmp_header(data, size, fd);
	print_pixels(data, fd);
	close(fd);
	exit(EXIT_SUCCESS);	
}


int	main(int argc, char **argv)
{
	int fd;
	t_data	data;
	t_list	*list;

	start(&data);
	fd = open(argv[1], O_RDONLY);
	check_error_save(&data, argc, argv, fd);
	data.conf.str_num = make_list(fd, &list);
	data.str = getinfo(&list, data.conf.str_num);
	get_resolution(data.str, &data, data.conf.str_num);
	data.conf.map_h = get_map(data.str, &data);
	check_map(&data);
	sprites_list(&data);
	get_player_location(&data);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, data.conf.win_w, data.conf.win_h, "Cub3D");
	data.img.img_ptr = mlx_new_image(data.mlx, data.conf.win_w, data.conf.win_h);
	data.img.img_addr = mlx_get_data_addr(data.img.img_ptr, &data.img.bits_per_pixel, &data.img.line_length, &data.img.endian);
	get_tex_path(data.str, &data, data.conf.str_num);
	get_textures(&data);
	get_floor_ceilling(data.str, &data, data.conf.str_num);
	launch(0, &data);
	if (data.save == 1)
		screen_shot(&data);
	mlx_hook(data.mlx_win, 2, 1L<<0, launch, &data);
	mlx_loop(data.mlx);
	return (0);
}