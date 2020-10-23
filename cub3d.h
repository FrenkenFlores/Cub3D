#ifndef CUB3D_H
# define CUB3D_H
# define TILE_SIZE 32
# define FOV_ANGLE 60 * M_PI / 180
# define STRIP_WIDTH 1
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"
# include "./mlx/mlx.h"


typedef struct s_list
{
    char			*content;
    struct s_list	*next;
}	t_list;

typedef struct s_position
{
	double	x;
	double	y;
}	t_position;

typedef struct s_ray
{
	float 	angel; //player.rotationAngel - (FOV_ANGLE / 2);
	double	wall_hit_x;
	double	wall_hit_y;
	double	horz_wall_hit_x;
	double	horz_wall_hit_y;
	double	vert_wall_hit_x;
	double	vert_wall_hit_y;
	double	distance;
	int		point_up;
	int		point_down;
	int		point_right;
	int		point_left;
	int		ray_hit_vertical_wall;		// to create the shadow effect
	int		found_horz_wall_hit;
	int 	found_vert_wall_hit;
	double	x_step;	// delta x
	double	y_step;	// delta y
	double		x_intercept;	// closest interception with the grid
	double 	y_intercept;
	double 	next_horz_y;
	double 	next_horz_x;
	double 	next_vert_y;
	double 	next_vert_x;

//	struct s_ray	*next_ray;
}	t_ray;

typedef struct s_player
{
	double		x;
	double		y;
	double		radius;
	float		rotation_angel;
	double		turn_direction;
	double		walk_directoin;
	double		move_speed;
	double		rotation_speed;
}	t_player;

typedef struct s_img
{
	void	*img_ptr;
	char	*img_addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_conf
{
	int		str_num;
	int		column;
	int		win_h;
	int		win_w;
	int		map_w;
	int		map_h;
	double	map_size;
	int		num_rays;
	int		cell_color;
	int		floor_color;
	char	**world_map;
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
	t_ray		**rays;
	t_img		img;
	t_img		tex[5];
	t_sprite	*sprite;
}	t_data;

#endif