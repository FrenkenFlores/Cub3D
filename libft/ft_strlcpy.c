/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 20:14:51 by fflores           #+#    #+#             */
/*   Updated: 2020/05/29 17:09:11 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int		i;
	int		j;
	size_t	n;

	i = 0;
	j = 0;
	n = size;
	if (!dst || !src)
		return (0);
	while (*src != '\0' && n != 1 && size > 0)
	{
		*dst++ = *src++;
		n--;
		j++;
	}
	if (size > 0)
		*dst = '\0';
	while (src[i] != '\0')
		i++;
	return (i + j);
}
