/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:14:27 by fflores           #+#    #+#             */
/*   Updated: 2020/11/04 16:14:29 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_textures_n_e(t_data *data)
{
	if (!(data->tex[0].img_ptr = mlx_xpm_file_to_image(data->mlx,
	data->conf.path_north, &data->tex[0].width, &data->tex[0].height)))
		ft_put_error("\nTexture dose not exist\n", EINVAL);
	data->tex[0].img_addr = mlx_get_data_addr(data->tex[0].img_ptr,
	&data->tex[0].bits_per_pixel, &data->tex[0].line_length,
	&data->tex[0].endian);
	if (!(data->tex[1].img_ptr = mlx_xpm_file_to_image(data->mlx,
	data->conf.path_east, &data->tex[1].width, &data->tex[1].height)))
		ft_put_error("\nTexture dose not exist\n", EINVAL);
	data->tex[1].img_addr = mlx_get_data_addr(data->tex[1].img_ptr,
	&data->tex[1].bits_per_pixel, &data->tex[1].line_length,
	&data->tex[1].endian);
}

static void	get_textures_s_w(t_data *data)
{
	if (!(data->tex[2].img_ptr = mlx_xpm_file_to_image(data->mlx,
	data->conf.path_south, &data->tex[2].width, &data->tex[2].height)))
		ft_put_error("\nTexture dose not exist\n", EINVAL);
	data->tex[2].img_addr = mlx_get_data_addr(data->tex[2].img_ptr,
	&data->tex[2].bits_per_pixel, &data->tex[2].line_length,
	&data->tex[2].endian);
	if (!(data->tex[3].img_ptr = mlx_xpm_file_to_image(data->mlx,
	data->conf.path_west, &data->tex[3].width, &data->tex[3].height)))
		ft_put_error("\nTexture dose not exist\n", EINVAL);
	data->tex[3].img_addr = mlx_get_data_addr(data->tex[3].img_ptr,
	&data->tex[3].bits_per_pixel, &data->tex[3].line_length,
	&data->tex[3].endian);
}

static void	get_textures_sp(t_data *data)
{
	if (!(data->tex[4].img_ptr = mlx_xpm_file_to_image(data->mlx,
	data->conf.path_sprite, &data->tex[4].width, &data->tex[4].height)))
		ft_put_error("\nTexture dose not exist\n", EINVAL);
	data->tex[4].img_addr = mlx_get_data_addr(data->tex[4].img_ptr,
	&data->tex[4].bits_per_pixel, &data->tex[4].line_length,
	&data->tex[4].endian);
}

void		get_textures(t_data *data)
{
	get_textures_n_e(data);
	get_textures_s_w(data);
	get_textures_sp(data);
}
