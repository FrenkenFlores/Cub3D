/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:43:42 by fflores           #+#    #+#             */
/*   Updated: 2020/11/02 18:43:43 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_min(int a, int b)
{
	return ((a < b) ? a : b);
}

int		ft_max(int a, int b)
{
	return ((a > b) ? a : b);
}

int		ft_numsize(int num)
{
	int size;

	size = 1;
	while (num / 10)
	{
		num = num / 10;
		size++;
	}
	return (size);
}

float	normalize_angle(double angle)
{
	double alpha;

	alpha = angle;
	while (alpha >= 2 * M_PI)
		alpha = alpha - 2 * M_PI;
	while (alpha < 0)
		alpha = alpha + 2 * M_PI;
	return ((float)alpha);
}

double	calculate_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
