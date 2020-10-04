/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 10:22:43 by fflores           #+#    #+#             */
/*   Updated: 2020/08/03 10:22:59 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_percent(t_flags flag)
{
	char	*ptr;

	if (!(ptr = ft_strdup("%")))
		return (NULL);
	if (flag.width && !flag.negative)
		if (!(ptr = ft_apply_width(flag.width, ptr, ' ')))
			return (NULL);
	if (flag.negative)
		if (!(ptr = ft_apply_rightwidth(flag.width, ptr, ' ')))
			return (NULL);
	return (ptr);
}
