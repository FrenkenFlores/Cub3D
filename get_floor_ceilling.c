/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_floor_ceilling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:10:57 by fflores           #+#    #+#             */
/*   Updated: 2020/11/02 15:10:59 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		check_after(char *str)
{
	int i;

	i = 1;
	while (str[i] == ' ')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == ',' || (str[i] >= '0' && str[i] <= '9'))
			i++;
		else
			ft_put_error("\nInvalid color parameters\n", EINVAL);
	}
}

static void		get_floor_color(char **str, t_data *data, int j)
{
	size_t		i;
	int			r;
	int			g;
	int			b;

	i = 0;
	while (i < ft_strlen(str[j]))
	{
		if (str[j][i] == 'F' && str[j][i + 1] == ' ')
		{
			i += 1;
			check_after(str[j]);
			while (str[j][i] == ' ')
				i++;
			r = ft_atoi(str[j] + i++);
			i += ft_numsize(r);
			g = ft_atoi(str[j] + i++);
			i += ft_numsize(g);
			b = ft_atoi(str[j] + i);
			data->conf.floor_color = rgb_hex(r, g, b);
			data->conf.double_key_f += 1;
			continue;
		}
		i++;
	}
}

static void		get_ceil_color(char **str, t_data *data, int j)
{
	size_t		i;
	int			r;
	int			g;
	int			b;

	i = 0;
	while (i < ft_strlen(str[j]))
	{
		if (str[j][i] == 'C' && str[j][i + 1] == ' ')
		{
			i += 1;
			check_after(str[j]);
			while (str[j][i] == ' ')
				i++;
			r = ft_atoi(str[j] + i++);
			i += ft_numsize(r);
			g = ft_atoi(str[j] + i++);
			i += ft_numsize(g);
			b = ft_atoi(str[j] + i);
			data->conf.ceill_color = rgb_hex(r, g, b);
			data->conf.double_key_c += 1;
			continue;
		}
		i++;
	}
}

void			get_floor_ceilling(char **str, t_data *data, size_t elm_count)
{
	size_t	j;

	j = 0;
	while (j < elm_count)
	{
		get_floor_color(str, data, j);
		get_ceil_color(str, data, j);
		j++;
	}
	if (data->conf.ceill_color < 0x000000 || data->conf.ceill_color > 0xFFFFFF
	|| data->conf.floor_color < 0x000000 || data->conf.floor_color > 0xFFFFFF)
		ft_put_error("\nInvalid color parameters\n", EINVAL);
	if (data->conf.double_key_c != 1 || data->conf.double_key_f != 1)
		ft_put_error("\nInvalid key\n", EINVAL);
}
