#include "cub3d.h"

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