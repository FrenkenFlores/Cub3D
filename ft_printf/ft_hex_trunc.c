/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_trunc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 10:17:41 by fflores           #+#    #+#             */
/*   Updated: 2020/08/03 10:17:53 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*ft_hex_precision(t_flags flag, char *ptr)
{
	if (flag.precision == 0 && ptr[0] == '0')
		ptr[0] = '\0';
	else
	{
		if (!(ptr = ft_apply_width(flag.precision, ptr, '0')))
			return (NULL);
	}
	if (flag.width)
		if (!(ptr = ft_apply_width(flag.width, ptr, ' ')))
			return (NULL);
	if (flag.negative)
		if (!(ptr = ft_align_left_side(ptr)))
			return (NULL);
	return (ptr);
}

static char		*ft_hex_without_precision(t_flags flag, char *ptr)
{
	if (flag.negative)
		return (ft_apply_rightwidth(flag.width, ptr, ' '));
	if (!flag.zero_flag)
		if (!(ptr = ft_apply_width(flag.width, ptr, ' ')))
			return (NULL);
	if (flag.zero_flag)
		if (!(ptr = ft_apply_width(flag.width, ptr, '0')))
			return (NULL);
	return (ptr);
}

char			*ft_hex_trunc(t_flags flag, t_parameters *prmtrs)
{
	char			*ptr;
	unsigned int	unsigned_value;

	unsigned_value = va_arg(prmtrs->ap, unsigned int);
	if (!(ptr = ft_hex_itoa(unsigned_value)))
		return (NULL);
	if (flag.dot)
		if (!(ptr = ft_hex_precision(flag, ptr)))
			return (NULL);
	if (!flag.dot)
		if (!(ptr = ft_hex_without_precision(flag, ptr)))
			return (NULL);
	return (ptr);
}
