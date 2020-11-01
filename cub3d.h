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
# include "./mlx/mlx.h"


typedef struct s_list
{
    char			*content;
    struct s_list	*next;
}	t_list;

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
	double	hit_sprite;
	double	x_step;	// delta x
	double	y_step;	// delta y
	double	x_intercept;	// closest interception with the grid
	double 	y_intercept;
	double 	next_horz_y;
	double 	next_horz_x;
	double 	next_vert_y;
	double 	next_vert_x;
}	t_ray;

typedef struct s_player
{
	double		x;
	double		y;
	double		radius;
	float		rotation_angel;
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
	char	*path_north;
	char	*path_east;
	char	*path_south;
	char	*path_west;
	char	*path_sprite;
	int		str_num;
	int		screen_size_x;
	int		screen_size_y;
	int		win_h;
	int		win_w;
	int		map_h;
	double	map_size;
	int		map_on_off;
	int		num_rays;
	unsigned long		ceill_color;
	unsigned long		floor_color;
	char	**world_map;
}	t_conf;

typedef struct s_sprite
{
	int			x;
	int			y;
	double			x1;
	double			y1;
	double			x2;
	double			y2;
	double		dir;
	double		distance;
	double		ray_hit_x;
	double		ray_hit_y;
	int		sprite_width;
	void		*next;
}	t_sprite;

typedef struct				s_sprite_list {
	int						spr_x;
	int						spr_y;
	int						len_from_plr;
	double					spr_dir;
	double					spr_scr_size;
	double					spr_scr_size1;
	double					h_offset;
	double					v_offset;
	double					step;
	int						i;
	int						j;
	int						count;
	int						color;
	struct s_spr_list		*next;
}							t_sprite_list;



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
	t_sprite_list *sprite_list;
}	t_data;



void	update(int keycode, t_data *data);
void	sprites_list(t_data *data);
void	sprites_conf(t_data *data);
t_img	scale_sprites(t_data *data, t_img tex, double scale, int tex_x);
void	put_sprite(t_data *data, t_sprite *sprite, t_ray *ray, int column_id, double scale, int projected_sprite_heigth);
void	render_sprites(t_data *data);
int		ft_min(int a, int b);
int		ft_max(int a, int b);
int		ft_numsize(int num);
float normalize_angle(double angle);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	mlx_pix_put(t_data *data, int x, int y, int color);
void	rect(t_data *data, double x, double y, int rect_width, int rect_height, int color);
void	circle(t_data *data, double x, double y, double radius, int color);
void	line(t_data *data, double x1, double y1, double x2, double y2, int color);
unsigned long rgb_hex(int r, int g, int b);
double calculate_distance(double x1, double y1, double x2, double y2);
int		point_in_vert_segment(t_data * data, t_ray *ray, t_sprite *sprite, int column_id);
int		point_in_horz_segment(t_data * data, t_ray *ray, t_sprite *sprite, int column_id);
int		point_in_segment(t_data * data, t_ray *ray, t_sprite *sprite, int column_id);
void	key_input(int keycode, t_data *data);
int		safe_distance(t_data *data, double player_x, double player_y);
void	mlx_close(t_data *data);
void	render_ceilling_floor(t_data *data);
void	render_map(t_data *data);
void	render_player(t_data *data);
void	render_rays(t_data *data);
void	free_rays_array(t_data *data);
void	ray_pointer(t_ray *ray);
void	ray_vert_hit_wall(t_ray *ray, t_data *data);
void	ray_horz_hit_wall(t_ray *ray, t_data *data);
int		is_wall(t_data *data, double x, double y);
void	render_walls(t_data *data);
void	texture_walls(t_data *data, t_ray *ray, int column_id, double scale, int projected_wall_heigth);
t_img	scale_textures(t_data *data, t_img tex, double scale, int tex_x);
t_img	choose_texture(t_data *data, t_ray *ray);
int		wall_color(t_ray *ray);
void	check_map(t_data *data);
int		check_zeros(char **world_map, int j, int i);
int		check_position(char **world_map, int j, int i);
void	check_error_save(t_data *data, int argc, char **argv, int fd);
void	ft_put_error(char *s, int id);
void	start(t_data *data);
size_t	make_list(int fd, t_list **list);
t_list	*push_back(char *str, t_list *old_list);
void	get_player_location(t_data *data);
void	get_resolution(char **str, t_data *data, size_t elm_count);
void	get_floor_ceilling(char **str, t_data *data, size_t elm_count);
void	get_tex_path(char **str, t_data *data, size_t elm_count);
int		get_map(char **ptr, t_data *data);
char	**getinfo(t_list **list, size_t elm_count);
void	get_textures(t_data *data);
void		ft_put_error(char *s, int id);













#endif