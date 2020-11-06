/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_double_key.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:15:14 by fflores           #+#    #+#             */
/*   Updated: 2020/11/04 13:15:15 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_double_key(t_data *data)
{
	if (data->conf.double_key_n != 1 || data->conf.double_key_e != 1
	|| data->conf.double_key_s != 1 || data->conf.double_key_w != 1
	|| data->conf.double_key_sp != 1 || data->conf.double_key_c != 1
	|| data->conf.double_key_f != 1 || data->conf.double_key_r != 1)
		ft_put_error("\nInvalid key or double key\n", EINVAL);
}
