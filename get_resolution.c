#include "cub3d.h"

static void	check_resolution(t_data *data)
{
	int sizex;
	int sizey;

	mlx_get_screen_size(data->mlx_win, &sizex, &sizey);
	data->conf.win_h = (data->conf.win_h > sizey) ? sizey : data->conf.win_h;
	data->conf.win_w = (data->conf.win_w > sizex) ? sizex : data->conf.win_w;
	data->conf.win_h = (data->conf.win_h < 300) ? 300 : data->conf.win_h;
	data->conf.win_w = (data->conf.win_w < 300) ? 300 : data->conf.win_w;
	if (data->conf.win_h <= 0 || data->conf.win_w <= 0)
		ft_put_error("\nInvalid resolution parameters\n", EINVAL);
}

void	get_resolution(char **str, t_data *data, size_t elm_count)
{
	size_t	j;
	size_t i;
	
	j = 0;
	while (j < elm_count)
	{
		i = 0;
		while (i < ft_strlen(str[j]))
		{
			if (str[j][i] == 'R')
			{
				i++;
				while (str[j][i] == ' ')
					i++;
				data->conf.win_w = ft_atoi(str[j] + i);
				i += ft_numsize(data->conf.win_w);
				while (str[j][i] == ' ')
					i++;
				data->conf.win_h = ft_atoi(str[j] + i);
			}
			i++;
		}
		j++;
	}
	check_resolution(data);
}