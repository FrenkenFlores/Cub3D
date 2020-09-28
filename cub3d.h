#ifndef CUB3D_H
# define CUB3D_H
# define H 600
# define W 800
# define PI 3.14159265359
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "./get_next_line/get_next_line.h"
# include "./mlx/mlx.h"


typedef struct s_list
{
    void			*content;
    struct s_list	*next;
}	t_list;

typedef struct s_position
{
	double	x;
	double	y;
}	t_position;

typedef struct s_player
{
	t_position	pos;
	double		dir;
	double		fov;
}	t_player;

typedef struct s_img
{
	void	*img_ptr;
	int		*img_addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_conf
{
	int		column;
	int		win_h;
	int		win_w;
	int		map_w;
	int		map_h;
	int		cell_color;
	int		floor_color;
	char	*world_map;
}	t_conf;

typedef struct s_sprite
{
	t_position	pos;
	double		dir;
	double		dist;
	int			screen_s;
	int			h_off;
	int			v_off;
	void		*next;
}	t_sprite;

typedef struct s_data
{
	double		depth_buffer[1920];
	void		*mlx;
	void		*mlx_win;
	char		**str;
	int			save;
	t_conf		conf;
	t_player	player;
	t_img		img;
	t_img		tex[5];
	t_sprite	*sprite;
}	t_data;

#endif