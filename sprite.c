#include "cub3d.h"

static t_sprite	*sort_sprite(t_data *all, t_sprite **ph)
{
	all->out = NULL;
	while (*ph)
	{
		all->q = *ph;
		*ph = (*ph)->next;
		all->p = all->out;
		all->pr = NULL;
		while (all->p && all->q->distance < all->p->distance)
		{
			all->pr = all->p;
			all->p = all->p->next;
		}
		if (all->pr == NULL)
		{
			all->q->next = all->out;
			all->out = all->q;
		}
		else
		{
			all->q->next = all->p;
			all->pr->next = all->q;
		}
	}
	*ph = all->out;
	return (*ph);
}

void	sprites_list(t_data *data)
{
	int i;
	int j;
	t_sprite *tmp;

	i = 0;
	j = 0;
	tmp = (t_sprite *)malloc(sizeof(t_sprite));
	data->sprite = tmp;
	while (j < data->conf.map_h)
	{
		i = 0;
		while (i < ft_strlen(data->conf.world_map[j]))
		{
			if (data->conf.world_map[j][i] == '2')
			{
				tmp->x = (i + 1) * TILE_SIZE;
				tmp->y = (j + 1) * TILE_SIZE;
				tmp->next = (t_sprite *)malloc(sizeof(t_sprite));
				tmp = tmp->next;
			}
			i++;
		}
		j++;
	}
	tmp->next = NULL;
}

void	sprites_conf(t_data *data)
{
	int x;
	int y;
	double angel;
	double a;
	t_sprite *tmp;

	tmp = data->sprite;
	a = atan((tmp->y - data->player.y) / (tmp->x - data->player.x));
	angel = M_PI_2;
	x = (data->tex[4].width / 2) * cos(a);
	y = (data->tex[4].width / 2) * sin(a);
	while (tmp != NULL)
	{				//rotation matrix
		tmp->x1 = tmp->x + (x * cos(angel) - y * sin(angel));
		tmp->y1 = tmp->y + (x * sin(angel) + y * cos(angel));
		tmp->x2 = tmp->x + (x * cos(angel) + y * sin(angel));
		tmp->y2 = tmp->y + (-1 * x * sin(angel) + y * cos(angel));
		tmp->distance = calculate_distance(data->player.x, data->player.y, tmp->x, tmp->y);
		tmp->sprite_width = calculate_distance(tmp->x1, tmp->y1, tmp->x2, tmp->y2);
		tmp = tmp->next;
	}
}

t_img	scale_sprites(t_data *data, t_img tex, double scale, int tex_x)
{
	t_img sc_tex;
	int y1;
	double y2;

	sc_tex.height = tex.height * scale;
	sc_tex.width = STRIP_WIDTH;
	sc_tex.img_ptr = mlx_new_image(data->mlx, sc_tex.width, sc_tex.height);
	sc_tex.img_addr = mlx_get_data_addr(sc_tex.img_ptr, &sc_tex.bits_per_pixel, &sc_tex.line_length, &sc_tex.endian);
	y1 = 0;
	y2 = 0;
	while (y1 < sc_tex.height)
	{
		*(unsigned int*)(sc_tex.img_addr + y1 * sc_tex.line_length + 0 * (sc_tex.bits_per_pixel / 8)) = *(unsigned int*)(tex.img_addr + (int)y2 * tex.line_length + tex_x * (tex.bits_per_pixel / 8));
		y1 += 1;
		y2 += 1 / scale;
	}
	return (sc_tex);
}

void	put_sprite(t_data *data, t_sprite *sprite, t_ray *ray, int column_id, double scale, int projected_sprite_heigth)
{
	t_img	tex;
	double tex_x;
	int tex_y;
	char *c;
	char *a;

	tex_y = 0;
	scale += (scale <= 0) ? 1 : 0;
	tex_x = (int)ray->hit_sprite % sprite->sprite_width;
	tex = scale_sprites(data, data->tex[4], scale, (int)tex_x);
	while (tex_y < tex.height)
	{
		c = data->img.img_addr + ((tex_y + (data->conf.win_h / 2 - projected_sprite_heigth / 2)) * data->img.line_length + column_id * (data->img.bits_per_pixel / 8));
		a = tex.img_addr + tex_y * tex.line_length + 0 * (tex.bits_per_pixel / 8);
		if (*(int*)a != 0xFFFFFF)
			*(int*)c = *(int*)a;
		tex_y++;
	}
}

void	render_sprites(t_data *data)
{
	int column_id;
	double distance_from_player_to_projection;
	double projected_sprite_heigth;
	double scale;
	t_sprite *tmp;

	tmp = data->sprite;
	distance_from_player_to_projection = data->conf.win_w / 2 * tanl(FOV_ANGLE / 2);
	sprites_conf(data);
	sort_sprite(data, &data->sprite);
	while (tmp)
	{
		column_id = 0;
		while(column_id < data->conf.num_rays)
		{
			scale = distance_from_player_to_projection / tmp->distance;
			projected_sprite_heigth = (data->tex[4].height * distance_from_player_to_projection) / tmp->distance;
			if (point_in_vert_segment(data, data->rays[column_id], tmp, column_id))
				put_sprite(data, tmp, data->rays[column_id], column_id, scale, projected_sprite_heigth);
			if (point_in_horz_segment(data, data->rays[column_id], tmp, column_id))
				put_sprite(data, tmp, data->rays[column_id], column_id, scale, projected_sprite_heigth);
			if (point_in_segment(data, data->rays[column_id], tmp, column_id))
				put_sprite(data, tmp, data->rays[column_id], column_id, scale, projected_sprite_heigth);
			column_id++;
		}
		tmp = tmp->next;
	}
}
