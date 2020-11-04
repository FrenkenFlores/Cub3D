/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_invalid_key.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:47:54 by fflores           #+#    #+#             */
/*   Updated: 2020/11/04 16:47:56 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_invalid_key(t_data *data, char **str)
{
	int i;
	int j;

	j = 0;
	while (j < data->conf.str_num)
	{
		i = -1;
		while (++i < (int)ft_strlen(str[j]))
		{
			if ((str[j][i] == 'N' && str[j][i + 1] == 'O')
			|| (str[j][i] == 'E' && str[j][i + 1] == 'A')
			|| (str[j][i] == 'S' && str[j][i + 1] == 'O')
			|| (str[j][i] == 'W' && str[j][i + 1] == 'E')
			|| (str[j][i] == 'F' && str[j][i + 1] == ' ')
			|| (str[j][i] == 'C' && str[j][i + 1] == ' ')
			|| (str[j][i] == 'S' && str[j][i + 1] == ' ')
			|| (str[j][i] == 'R' && str[j][i + 1] == ' ')
			|| (str[j][i] == '1') || (str[j][i] == ' ')
			|| (str[j][i] == '\n') || (str[j][i] == '\t'))
				break ;
			else
				ft_put_error("\nInvalid key\n", EINVAL);
		}
		j++;
	}
}
