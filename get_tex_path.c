/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tex_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:29:07 by fflores           #+#    #+#             */
/*   Updated: 2020/11/02 15:29:08 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		find_no_so(char **str, t_data *data, int j)
{
	int i;

	i = 0;
	while (i < (int)ft_strlen(str[j]))
	{
		if (str[j][i] == 'N' && str[j][i + 1] == 'O' && str[j][i + 2] == ' ')
		{
			i += 2;
			while (str[j][i] == ' ')
				i++;
			data->conf.path_north = &(str[j][i]);
			data->conf.double_key_n += 1;
			continue;
		}
		if (str[j][i] == 'S' && str[j][i + 1] == 'O' && str[j][i + 2] == ' ')
		{
			i += 2;
			while (str[j][i] == ' ')
				i++;
			data->conf.path_south = &(str[j][i]);
			data->conf.double_key_s += 1;
			continue;
		}
		i++;
	}
}

static void		find_ea_we(char **str, t_data *data, int j)
{
	int i;

	i = 0;
	while (i < (int)ft_strlen(str[j]))
	{
		if (str[j][i] == 'E' && str[j][i + 1] == 'A' && str[j][i + 2] == ' ')
		{
			i += 2;
			while (str[j][i] == ' ')
				i++;
			data->conf.path_east = &(str[j][i]);
			data->conf.double_key_e += 1;
			continue;
		}
		if (str[j][i] == 'W' && str[j][i + 1] == 'E' && str[j][i + 2] == ' ')
		{
			i += 2;
			while (str[j][i] == ' ')
				i++;
			data->conf.path_west = &(str[j][i]);
			data->conf.double_key_w += 1;
			continue;
		}
		i++;
	}
}

static void		find_sprite(char **str, t_data *data, int j)
{
	int i;

	i = 0;
	while (i < (int)ft_strlen(str[j]))
	{
		if (str[j][i] == 'S' && str[j][i + 1] == ' ')
		{
			i += 1;
			while (str[j][i] == ' ')
				i++;
			data->conf.path_sprite = &(str[j][i]);
			data->conf.double_key_sp += 1;
			continue;
		}
		i++;
	}
}

void			get_tex_path(char **str, t_data *data, size_t elm_count)
{
	size_t	j;

	j = 0;
	while (j < elm_count)
	{
		find_no_so(str, data, j);
		find_ea_we(str, data, j);
		find_sprite(str, data, j);
		j++;
	}
	check_invalid_key(data, str);
	if (!(data->conf.path_east) || !(data->conf.path_west)
	|| !(data->conf.path_south) || !(data->conf.path_north)
	|| !(data->conf.path_sprite))
		ft_put_error("\nDid not find the textures\n", EINVAL);
}
