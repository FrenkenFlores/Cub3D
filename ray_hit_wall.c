/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 17:49:31 by fflores           #+#    #+#             */
/*   Updated: 2020/11/02 17:49:33 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ray_pointer(t_ray *ray)
{
	ray->point_down = (ray->angel >= 0 && ray->angel < M_PI) ? 1 : 0;
	ray->point_up = !ray->point_down;
	ray->point_left =
	(ray->angel >= M_PI / 2 && ray->angel < 3 * M_PI / 2) ? 1 : 0;
	ray->point_right = !ray->point_left;
}

static void	ray_v_config(t_data *data, t_ray *ray)
{
	ray->f_v_w_h = 0;
	ray->dx = (int)(data->player.x / TILE_SIZE) * TILE_SIZE;
	ray->dx += (ray->point_right) ? TILE_SIZE : 0;
	ray->dy =
	data->player.y + (ray->dx - data->player.x) * tan(ray->angel);
	ray->x_step = TILE_SIZE;
	ray->x_step *= (ray->point_left) ? -1 : 1;
	ray->y_step = TILE_SIZE * tan(ray->angel);
	ray->y_step *= (ray->point_up && ray->y_step > 0) ? -1 : 1;
	ray->y_step *= (ray->point_down && ray->y_step < 0) ? -1 : 1;
	ray->next_vert_x = ray->dx;
	ray->next_vert_y = ray->dy;
	ray->v_w_h_x = 0;
	ray->v_w_h_y = 0;
}

static void	ray_h_config(t_data *data, t_ray *ray)
{
	ray->f_h_w_h = 0;
	ray->dy = (int)(data->player.y / TILE_SIZE) * TILE_SIZE;
	ray->dy += (ray->point_down) ? TILE_SIZE : 0;
	ray->dx = data->player.x + (ray->dy - data->player.y) / tan(ray->angel);
	ray->y_step = TILE_SIZE;
	ray->y_step *= (ray->point_up) ? -1 : 1;
	ray->x_step = TILE_SIZE / tan(ray->angel);
	ray->x_step *= (ray->point_right && ray->x_step < 0) ? -1 : 1;
	ray->x_step *= (ray->point_left && ray->x_step > 0) ? -1 : 1;
	ray->next_horz_x = ray->dx;
	ray->next_horz_y = ray->dy;
	ray->h_w_h_x = 0;
	ray->h_w_h_y = 0;
}

void		ray_vert_hit_wall(t_ray *ray, t_data *data)
{
	ray_v_config(data, ray);
	while (ray->f_v_w_h == 0)
	{
		if (ray->next_vert_y > 0 && is_wall(data,
		ray->next_vert_x - (ray->point_left ? 1 : 0), ray->next_vert_y) == 1)
		{
			ray->v_w_h_x = ray->next_vert_x;
			ray->v_w_h_y = ray->next_vert_y;
			ray->f_v_w_h = 1;
			break ;
		}
		else if (is_wall(data,
		ray->next_vert_x - (ray->point_left ? 1 : 0), ray->next_vert_y) == -1)
			break ;
		else
		{
			ray->next_vert_x += ray->x_step;
			ray->next_vert_y += ray->y_step;
		}
	}
}

void		ray_horz_hit_wall(t_ray *ray, t_data *data)
{
	ray_h_config(data, ray);
	while (ray->f_h_w_h == 0)
	{
		if (is_wall(data,
		ray->next_horz_x, ray->next_horz_y - (ray->point_up ? 1 : 0)) == 1)
		{
			ray->h_w_h_x = ray->next_horz_x;
			ray->h_w_h_y = ray->next_horz_y;
			ray->f_h_w_h = 1;
			break ;
		}
		else if (is_wall(data,
		ray->next_horz_x, ray->next_horz_y - (ray->point_up ? 1 : 0)) == -1)
			break ;
		else
		{
			ray->next_horz_x += ray->x_step;
			ray->next_horz_y += ray->y_step;
		}
	}
}
