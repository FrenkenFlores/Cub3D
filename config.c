/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:14:25 by fflores           #+#    #+#             */
/*   Updated: 2020/11/02 14:25:06 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start(t_data *data)
{
	data->rays = NULL;
	data->conf.win_h = -1;
	data->conf.win_w = -1;
	data->player.x = 0;
	data->player.y = 0;
	data->player.radius = 16;
	data->player.rotation_angel = 0;
	data->player.move_speed = 5.0;
	data->player.rotation_speed = 4 * (M_PI / 180);
	data->conf.map_h = -1;
	data->conf.map_size = 0.3;
	data->conf.world_map = NULL;
	data->conf.floor_color = -1;
	data->conf.ceill_color = -1;
	data->sprite = NULL;
	data->conf.double_key_r = 0;
	data->conf.double_key_n = 0;
	data->conf.double_key_e = 0;
	data->conf.double_key_s = 0;
	data->conf.double_key_w = 0;
	data->conf.double_key_sp = 0;
	data->conf.double_key_c = 0;
	data->conf.double_key_f = 0;
	data->save = 0;
}

int		get_map(char **ptr, t_data *data)
{
	size_t j;
	size_t i;

	j = data->conf.str_num - 1;
	while (j > 0)
	{
		i = 0;
		while (i < ft_strlen(ptr[j]))
		{
			if (ptr[j][i] == ' ' || ptr[j][i] == '0' || ptr[j][i] == '1'
			|| ptr[j][i] == '2' || ptr[j][i] == 'N' || ptr[j][i] == 'E'
			|| ptr[j][i] == 'S' || ptr[j][i] == 'W')
				i++;
			else
				break ;
		}
		if (i != ft_strlen(ptr[j]))
			break ;
		j--;
	}
	data->conf.world_map = &ptr[++j];
	if (j == 0)
		ft_put_error("\nMap dose not exist\n", EINVAL);
	return (data->conf.str_num - j);
}

char	**getinfo(t_list **list, size_t elm_count)
{
	char		**ptr;
	t_list		*tmp;
	size_t		j;

	tmp = *list;
	j = elm_count;
	ptr = (char**)malloc((sizeof(char*) * j) + 2);
	while (tmp && j >= 0)
	{
		ptr[j - 1] = tmp->content;
		tmp = tmp->next;
		j--;
	}
	ptr[elm_count++] = "";
	ptr[elm_count] = NULL;
	return (ptr);
}
