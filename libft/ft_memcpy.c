/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 17:33:50 by fflores           #+#    #+#             */
/*   Updated: 2020/05/23 22:50:20 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	size_t		i;
	char		*start;

	if (dst || src)
	{
		i = 0;
		start = (char*)dst;
		while (i < n)
		{
			*(char*)dst++ = *(char*)src++;
			i++;
		}
		return (start);
	}
	return (NULL);
}
