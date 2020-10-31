#include "cub3d.h"

void	update(int keycode, t_data *data)
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

int	main(int argc, char **argv)
{
	int fd;
	size_t	elm_count;
	t_data	data;
	t_list	*list;

	start(&data);
	fd = open(argv[1], O_RDONLY);
	check_error_save(&data, argc, argv, fd);
	elm_count = make_list(fd, &list);
	data.conf.str_num = elm_count;
	data.str = getinfo(&list, elm_count);
	get_resolution(data.str, &data, elm_count);
	data.conf.map_h = get_map(data.str, &data);
	check_map(&data);
	sprites_list(&data);
	get_player_location(&data);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, data.conf.win_w, data.conf.win_h, "Cub3D");
	data.img.img_ptr = mlx_new_image(data.mlx, data.conf.win_w, data.conf.win_h);
	data.img.img_addr = mlx_get_data_addr(data.img.img_ptr, &data.img.bits_per_pixel, &data.img.line_length, &data.img.endian);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img.img_ptr, 0, 0);
	get_tex_path(data.str, &data, elm_count);
	get_textures(&data);
	get_floor_ceilling(data.str, &data, elm_count);
	mlx_hook(data.mlx_win, 2, 1L<<0, update, &data);
	mlx_loop(data.mlx);
	return (0);
}