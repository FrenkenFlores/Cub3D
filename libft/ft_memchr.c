/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 10:32:49 by fflores           #+#    #+#             */
/*   Updated: 2020/05/23 18:35:34 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	unsigned char *tmp;
	unsigned char chr;

	if (src || c == '\0')
	{
		tmp = (unsigned char*)src;
		chr = (unsigned char)c;
		while (n--)
		{
			if (*tmp == chr)
				return (tmp);
			tmp++;
		}
	}
	return (NULL);
}
