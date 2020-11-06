/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_resolution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:27:55 by fflores           #+#    #+#             */
/*   Updated: 2020/11/02 15:27:57 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_after(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			ft_put_error("\nInvalid resolution parameters\n", EINVAL);
		i++;
	}
}

static void	check_resolution(t_data *data)
{
	int sizex;
	int sizey;

	if (data->conf.win_w == -1 || data->conf.win_h == -1)
		ft_put_error("\ndid not find the resolution key\n", EINVAL);
	mlx_get_screen_size(data->mlx_win, &sizex, &sizey);
	if (data->conf.win_h > sizey || data->conf.win_h > INT32_MAX)
		data->conf.win_h = sizey;
	if (data->conf.win_w > sizex || data->conf.win_w > INT32_MAX)
		data->conf.win_w = sizex;
	if (data->conf.win_h <= 0 || data->conf.win_w <= 0)
		ft_put_error("\nInvalid resolution parameters\n", EINVAL);
	data->conf.num_rays = data->conf.win_w / STRIP_WIDTH;
}

void		get_resolution(char **str, t_data *data, size_t elm_count)
{
	size_t	j;
	size_t	i;

	j = -1;
	while (++j < elm_count)
	{
		i = -1;
		while (++i < ft_strlen(str[j]) && str[j][i] != '\0')
		{
			if (str[j][i++] == 'R')
			{
				data->conf.double_key_r += 1;
				while (str[j][i] == ' ')
					i++;
				data->conf.win_w = ft_atoi(str[j] + i);
				i += ft_numsize(data->conf.win_w);
				while (str[j][i] == ' ')
					i++;
				data->conf.win_h = ft_atoi(str[j] + i);
				i += ft_numsize(data->conf.win_h);
				check_after(str[j] + i);
			}
		}
	}
	check_resolution(data);
}
