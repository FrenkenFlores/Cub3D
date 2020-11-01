#include "cub3d.h"

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
				data->conf.num_sprites++;
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
	{
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

static void bubble_sort(int a[], int n) {
    int i = 0, j = 0, tmp;
    for (i = 0; i < n; i++) 
	{   // loop n times - 1 per element
        for (j = 0; j < n - i - 1; j++) 
		{ // last i elements are sorted already
            if (a[j] > a[j + 1]) 
			{  // swop if order is broken
                tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
}
/*
void sort_list(t_sprite *head) 
{
	t_sprite *a = NULL;
	t_sprite *b = NULL; 
	t_sprite *c = NULL;
	t_sprite*e = NULL; 
	t_sprite *tmp = NULL; 
 
	while(e != head->next) 
	{
		c = a = head;
		b = a->next;
		while(a != e) 
		{
			if(a->distance > b->distance) 
			{
				if(a == head) 
				{
					tmp = b -> next;
					b->next = a;
					a->next = tmp;
					head = b;
					c = b;
				} 
				else 
				{
					tmp = b->next;
					b->next = a;
					a->next = tmp;
					c->next = b;
					c = b;
				}
			} 
			else 
			{
				c = a;
				a = a->next;
			}
			b = a->next;
			if(b == e)
			e = a;
		}
	}
}
*/
void sort_list(t_sprite *sprite, int num_sprites)
{
	t_sprite *start = sprite;
	t_sprite *p = sprite;
	t_sprite *q = sprite->next;
	t_sprite *tmp = NULL;
	int i;

	i = 0;
	while (i <= num_sprites)
	{
		if (p->distance > q->distance)
		{
			tmp = q->next;
			q->next = p;
			p->next = tmp;
		}
		else
		{
			p = p->next;
			q = q->next;
		}
//		if (q == NULL)
//		{
//			p = sprite;
//			q = sprite->next;
//		}
		i++;
	}
}

void	render_sprites(t_data *data)
{
	int column_id;
	double distance_from_player_to_projection;
	double projected_sprite_heigth;
	double scale;
	t_sprite *tmp;
	t_sprite *tmp2;

	distance_from_player_to_projection = data->conf.win_w / 2 * tanl(FOV_ANGLE / 2);
	sprites_conf(data);
//	sort_list(data->sprite, data->conf.num_sprites);
	tmp = data->sprite;
//	tmp2 = data->sprite;
//	for(int j = 0; j < data->conf.num_sprites; j++)
//	{
//		printf("%i - %f\n", j, tmp2->distance);
//		tmp2 = tmp2->next;
//	}
	while (tmp->next)
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
