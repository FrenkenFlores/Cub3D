/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 19:25:18 by fflores           #+#    #+#             */
/*   Updated: 2020/05/23 17:14:26 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, void *src, int c, size_t n)
{
	if (dst || src)
	{
		while (n--)
		{
			*((char*)dst++) = *((char*)src++);
			if (*((unsigned char*)dst - 1) == (unsigned char)c)
				return ((char*)dst);
		}
		return (NULL);
	}
	return (NULL);
}
