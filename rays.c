#include "cub3d.h"

void	render_rays(t_data *data)
{
	t_ray *ray;
	int column_id;
	int num_rays;
	float angel;
	double horz_distance;
	double vert_distance;

	column_id = 0;
	angel = data->player.rotation_angel - (FOV_ANGLE / 2);
	num_rays = data->conf.win_w / STRIP_WIDTH;
	if (data->rays)
		free_rays_array(data);
	if (!(data->rays = (t_ray **)malloc(sizeof(t_ray *) * num_rays)))
		exit(EXIT_FAILURE);
	while(column_id < num_rays)
	{
		if(!(ray = (t_ray *)malloc(sizeof(t_ray))))
			exit(EXIT_FAILURE);
		ray->angel = normalize_angle(angel);
		ray_pointer(ray);
		if (ray->angel != 0 || ray->angel != M_PI)
			ray_horz_hit_wall(ray, data);
		if (ray->angel != (M_PI / 2) || ray->angel != (3 * M_PI / 2))
			ray_vert_hit_wall(ray, data);
		horz_distance = (ray->found_horz_wall_hit) ? calculate_distance(data->player.x, data->player.y, ray->horz_wall_hit_x, ray->horz_wall_hit_y) : INFINITY;
		vert_distance = (ray->found_vert_wall_hit) ? calculate_distance(data->player.x, data->player.y, ray->vert_wall_hit_x, ray->vert_wall_hit_y) : INFINITY;
		ray->wall_hit_x = (horz_distance < vert_distance) ? ray->horz_wall_hit_x : ray->vert_wall_hit_x;
		ray->wall_hit_y = (horz_distance < vert_distance) ? ray->horz_wall_hit_y : ray->vert_wall_hit_y;
		ray->distance = (horz_distance < vert_distance) ? horz_distance : vert_distance;

		ray->ray_hit_vertical_wall = (horz_distance > vert_distance) ? 1 : 0;
		if (data->conf.map_on_off == 1)
			line(data,data->player.x * data->conf.map_size, data->player.y * data->conf.map_size, ray->wall_hit_x * data->conf.map_size, ray->wall_hit_y * data->conf.map_size, 0xFFFF00);
		data->rays[column_id] = ray;
		angel += FOV_ANGLE / num_rays;
		column_id++;
	}
	data->conf.num_rays = num_rays;
}
void	free_rays_array(t_data *data)
{
	int i;

	i = 0;
	while (i < data->conf.num_rays)
	{
		if (data->rays[i])
			free (data->rays[i]);
		i++;
	}
	free (data->rays);
}
void	ray_pointer(t_ray *ray)
{
	ray->point_down = (ray->angel >= 0 && ray->angel < M_PI) ? 1 : 0;
	ray->point_up = !ray->point_down;
	ray->point_left = (ray->angel >= M_PI / 2 && ray->angel < 3 * M_PI / 2) ? 1 : 0;
	ray->point_right = !ray->point_left;
}
void	ray_vert_hit_wall(t_ray *ray, t_data *data)
{
	ray->found_vert_wall_hit = 0;
	ray->x_intercept = (int)(data->player.x / TILE_SIZE) * TILE_SIZE;
	ray->x_intercept += (ray->point_right) ? TILE_SIZE : 0;
	ray->y_intercept = data->player.y + (ray->x_intercept - data->player.x) * tan(ray->angel);
	ray->x_step = TILE_SIZE;
	ray->x_step *= (ray->point_left) ? -1 : 1;
	ray->y_step = TILE_SIZE * tan(ray->angel);
	ray->y_step *= (ray->point_up && ray->y_step > 0) ? -1 : 1;
	ray->y_step *= (ray->point_down && ray->y_step < 0) ? -1 : 1;
	ray->next_vert_x = ray->x_intercept;
	ray->next_vert_y = ray->y_intercept;
	ray->vert_wall_hit_x = 0;
	ray->vert_wall_hit_y = 0;
	while (ray->found_vert_wall_hit == 0)
	{
		if (ray->next_vert_y > 0 && is_wall(data, ray->next_vert_x - (ray->point_left ? 1 : 0), ray->next_vert_y) == 1)
		{
			ray->vert_wall_hit_x = ray->next_vert_x;
			ray->vert_wall_hit_y = ray->next_vert_y;
			ray->found_vert_wall_hit = 1;
			break;
		}
		else if (is_wall(data, ray->next_vert_x - (ray->point_left ? 1 : 0), ray->next_vert_y) == -1)
			break;
		else
		{
			ray->next_vert_x += ray->x_step;
			ray->next_vert_y += ray->y_step;
		}
	}
}

void	ray_horz_hit_wall(t_ray *ray, t_data *data)
{
	ray->found_horz_wall_hit = 0;
	ray->y_intercept = (int)(data->player.y / TILE_SIZE) * TILE_SIZE;
	ray->y_intercept += (ray->point_down) ? TILE_SIZE : 0;
	ray->x_intercept = data->player.x + (ray->y_intercept - data->player.y) / tan(ray->angel);
	ray->y_step = TILE_SIZE;
	ray->y_step *= (ray->point_up) ? -1 : 1;
	ray->x_step = TILE_SIZE / tan(ray->angel);
	ray->x_step *= (ray->point_right && ray->x_step < 0) ? -1 : 1;
	ray->x_step *= (ray->point_left && ray->x_step > 0) ? -1 : 1;
	ray->next_horz_x = ray->x_intercept;
	ray->next_horz_y = ray->y_intercept;
	ray->horz_wall_hit_x = 0;
	ray->horz_wall_hit_y = 0;
	while (ray->found_horz_wall_hit == 0)
	{
		if (is_wall(data, ray->next_horz_x, ray->next_horz_y - (ray->point_up ? 1 : 0)) == 1)
		{
			ray->horz_wall_hit_x = ray->next_horz_x;
			ray->horz_wall_hit_y = ray->next_horz_y;
			ray->found_horz_wall_hit = 1;
			break;
		}
		else if (is_wall(data, ray->next_horz_x, ray->next_horz_y - (ray->point_up ? 1 : 0)) == -1)
			break;
		else
		{
			ray->next_horz_x += ray->x_step;
			ray->next_horz_y += ray->y_step;
		}	
	}
}
int		is_wall(t_data *data, double x, double y)
{
	int map_index_x;
	int map_index_y;

	map_index_x = (int)(x / TILE_SIZE);
	map_index_y = (int)(y / TILE_SIZE);
	if (map_index_x < 0 || map_index_x > data->conf.win_w || map_index_y < 0 || map_index_y > data->conf.win_h || map_index_y >= data->conf.map_h)
			return (-1);
	if (ft_strlen(data->conf.world_map[map_index_y]) > map_index_x)
		return (data->conf.world_map[map_index_y][map_index_x] == '1' ? 1 : 0);
	return (-1);
}