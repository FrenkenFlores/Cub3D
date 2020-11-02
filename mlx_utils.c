/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:54:38 by fflores           #+#    #+#             */
/*   Updated: 2020/11/02 18:54:40 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			mlx_pix_put(t_data *data, int x, int y, int color)
{
	char	*pos;
	int		offset;

	offset = y * data->img.line_length + x * (data->img.bits_per_pixel / 8);
	pos = data->img.img_addr + offset;
	*(unsigned int*)pos = color;
}

unsigned long	rgb_hex(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}
