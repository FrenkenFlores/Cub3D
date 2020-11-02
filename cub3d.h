/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:29:00 by fflores           #+#    #+#             */
/*   Updated: 2020/11/02 14:29:09 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define TILE_SIZE 32
# define FOV_ANGLE 90 * M_PI / 180
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
//# include "./mlx_statlib/mlx.h"
# include "./mlx_dylib/mlx.h"

typedef struct	s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

typedef struct	s_ray
{
	float	angel;
	double	wall_hit_x;
	double	wall_hit_y;
	double	h_w_h_x;
	double	h_w_h_y;
	double	v_w_h_x;
	double	v_w_h_y;
	double	distance;
	int		point_up;
	int		point_down;
	int		point_right;
	int		point_left;
	int		ray_hit_vertical_wall;
	int		f_h_w_h;
	int		f_v_w_h;
	double	hit_sprite;
	double	x_step;
	double	y_step;
	double	dx;
	double	dy;
	double	next_horz_y;
	double	next_horz_x;
	double	next_vert_y;
	double	next_vert_x;
}				t_ray;

typedef struct	s_player
{
	double		x;
	double		y;
	double		radius;
	float		rotation_angel;
	double		move_speed;
	double		rotation_speed;
}				t_player;

typedef struct	s_img
{
	void	*img_ptr;
	char	*img_addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct	s_conf
{
	double			projected_wall_heigth;
	char			*path_north;
	char			*path_east;
	char			*path_south;
	char			*path_west;
	char			*path_sprite;
	int				str_num;
	int				screen_size_x;
	int				screen_size_y;
	int				win_h;
	int				win_w;
	int				map_h;
	double			map_size;
	int				num_rays;
	unsigned long	ceill_color;
	unsigned long	floor_color;
	char			**world_map;
}				t_conf;

typedef struct	s_sprite
{
	double	spr_dir;
	int		i;
	int		j;
	double	step;
	int		count;
	int		color;
	int		x;
	int		y;
	double	x1;
	double	y1;
	double	x2;
	double	y2;
	double	dir;
	double	distance;
	double	ray_hit_x;
	double	ray_hit_y;
	int		sprite_w;
	int		sprite_h;
	double	h_offset;
	double	v_offset;
	void	*next;
}				t_sprite;

typedef struct	s_data
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
	t_sprite	*out;
	t_sprite	*q;
	t_sprite	*p;
	t_sprite	*pr;

}				t_data;

t_sprite		*sort_sprite(t_data *all, t_sprite **ph);
void			sprites_conf(t_data *data);
void			screen_shot(t_data *data);
void			sprites_list(t_data *data);
void			render_sprites(t_data *data);
int				ft_min(int a, int b);
int				ft_max(int a, int b);
int				ft_numsize(int num);
float			normalize_angle(double angle);
void			mlx_pix_put(t_data *data, int x, int y, int color);
unsigned long	rgb_hex(int r, int g, int b);
double			calculate_distance(double x1, double y1,
				double x2, double y2);
int				point_in_vert_segment(t_data *data, t_ray *ray,
				t_sprite *sprite, int column_id);
int				point_in_horz_segment(t_data *data, t_ray *ray,
				t_sprite *sprite, int column_id);
int				point_in_segment(t_data *data, t_ray *ray,
				t_sprite *sprite, int column_id);
void			key_input(int keycode, t_data *data);
int				safe_distance(t_data *data, double player_x, double player_y);
void			mlx_close(t_data *data);
void			render_ceilling_floor(t_data *data);
void			render_rays(t_data *data);
void			free_rays_array(t_data *data);
void			ray_pointer(t_ray *ray);
void			ray_vert_hit_wall(t_ray *ray, t_data *data);
void			ray_horz_hit_wall(t_ray *ray, t_data *data);
int				is_wall(t_data *data, double x, double y);
void			render_walls(t_data *data);
void			texture_walls(t_data *data, t_ray *ray, int column_id,
				double scale);
t_img			scale_textures(t_data *data, t_img tex,
				double scale, int tex_x);
t_img			choose_texture(t_data *data, t_ray *ray);
int				wall_color(t_ray *ray);
void			check_map(t_data *data);
int				check_zeros(char **world_map, int j, int i);
void			check_player(int detcted);
void			check_error_save(t_data *data, int argc, char **argv, int fd);
void			ft_put_error(char *s, int id);
void			start(t_data *data);
size_t			make_list(int fd, t_list **list);
void			get_player_location(t_data *data);
void			get_resolution(char **str, t_data *data, size_t elm_count);
void			get_floor_ceilling(char **str, t_data *data, size_t elm_count);
void			get_tex_path(char **str, t_data *data, size_t elm_count);
int				get_map(char **ptr, t_data *data);
char			**getinfo(t_list **list, size_t elm_count);
void			get_textures(t_data *data);
#endif
