/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ceilling_floor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:59:31 by fflores           #+#    #+#             */
/*   Updated: 2020/11/02 18:59:33 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_ceilling_floor(t_data *data)
{
	int i;
	int j;

	j = 0;
	while (j < data->conf.win_h)
	{
		i = -1;
		while (++i < data->conf.win_w)
			mlx_pix_put(data, 0 + i, 0 + j, data->conf.ceill_color);
		j++;
	}
	j = 0;
	while (j < data->conf.win_h / 2)
	{
		i = -1;
		while (++i < data->conf.win_w)
			mlx_pix_put(data, 0 + i, data->conf.win_h
			/ 2 + j, data->conf.floor_color);
		j++;
	}
}
