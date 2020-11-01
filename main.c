#include "cub3d.h"

static void	update(int keycode, t_data *data)
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

static void mlx(t_data *data)
{
	if (!(data->mlx = mlx_init()))
		exit(EXIT_FAILURE);
	if (!(data->mlx_win = mlx_new_window(data->mlx, data->conf.win_w, data->conf.win_h, "Cub3D")))
		exit(EXIT_FAILURE);
	if (!(data->img.img_ptr = mlx_new_image(data->mlx, data->conf.win_w, data->conf.win_h)))
		exit(EXIT_FAILURE);
	if (!(data->img.img_ptr = mlx_new_image(data->mlx, data->conf.win_w, data->conf.win_h)))
		exit(EXIT_FAILURE);
	if (!(data->img.img_addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian)))
		exit(EXIT_FAILURE);
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
	mlx(&data);
	data.conf.map_h = get_map(data.str, &data);
	check_map(&data);
	sprites_list(&data);
	get_player_location(&data);
	get_tex_path(data.str, &data, data.conf.str_num);
	get_textures(&data);
	get_floor_ceilling(data.str, &data, data.conf.str_num);
	mlx_hook(data.mlx_win, 2, 1L<<0, update, &data);
	mlx_hook(data.mlx_win, 17, 1L<<0, mlx_close, 0);
	mlx_loop(data.mlx);
	return (0);
}