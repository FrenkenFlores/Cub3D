/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 09:56:58 by fflores           #+#    #+#             */
/*   Updated: 2020/08/03 09:59:10 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_atoi(const char *str, t_parameters *param)
{
	int				i;
	int				negative;
	unsigned long	return_value;

	i = 0;
	negative = 1;
	return_value = 0;
	if (!str)
		return (0);
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		return_value = return_value * 10 + str[i++] - '0';
	param->count = param->count +
		ft_atoi_length((int)return_value * negative) - 1;
	return ((int)return_value * negative);
}
