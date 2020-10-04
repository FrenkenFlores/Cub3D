/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 10:35:05 by fflores           #+#    #+#             */
/*   Updated: 2020/08/03 10:35:18 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_str(t_flags flag, t_parameters *prmtrs)
{
	char	*ptr;

	if (!(ptr = va_arg(prmtrs->ap, char *)))
	{
		if (!(ptr = ft_strdup("(null)")))
			return (NULL);
	}
	else
	{
		if (!(ptr = ft_strdup(ptr)))
			return (NULL);
	}
	if (flag.dot)
		if (!(ptr = ft_get_precision(flag.precision, ptr)))
			return (NULL);
	if (flag.width)
		if (!(ptr = ft_apply_width(flag.width, ptr, ' ')))
			return (NULL);
	if (flag.negative)
		ptr = ft_align_left_side(ptr);
	return (ptr);
}

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	if (src != NULL && dst != NULL && dstsize != 0)
	{
		while (i < (dstsize - 1) && src[i])
		{
			dst[i] = src[i];
			i++;
		}
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
