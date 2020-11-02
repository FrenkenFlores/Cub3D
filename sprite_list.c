/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:06:58 by fflores           #+#    #+#             */
/*   Updated: 2020/11/02 18:07:00 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		sprites_list(t_data *data)
{
	int			i;
	int			j;
	t_sprite	*tmp;

	i = 0;
	j = 0;
	tmp = (t_sprite *)malloc(sizeof(t_sprite));
	data->sprite = tmp;
	while (j < data->conf.map_h)
	{
		i = 0;
		while (i < (int)ft_strlen(data->conf.world_map[j]))
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

t_sprite	*sort_sprite(t_data *all, t_sprite **ph)
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

void		sprites_conf(t_data *data)
{
	int			x;
	int			y;
	double		a;
	t_sprite	*tmp;

	tmp = data->sprite;
	a = atan((tmp->y - data->player.y) / (tmp->x - data->player.x));
	x = (data->tex[4].width / 2) * cos(a);
	y = (data->tex[4].width / 2) * sin(a);
	while (tmp != NULL)
	{
		tmp->distance =
		calculate_distance(data->player.x, data->player.y, tmp->x, tmp->y);
		tmp = tmp->next;
	}
}
