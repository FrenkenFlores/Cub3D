/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 02:57:45 by fflores           #+#    #+#             */
/*   Updated: 2020/05/23 18:25:16 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void *src, size_t n)
{
	char *str1;

	str1 = (char*)dst;
	if (dst || src)
	{
		if (n == 0)
			return (dst);
		if (str1 > (char*)src)
		{
			str1 = str1 + n - 1;
			src = src + n - 1;
			while (n-- > 0)
				*str1-- = *((char*)src--);
		}
		else
		{
			while (n > 0)
			{
				*str1++ = *((char*)src++);
				n--;
			}
		}
		return (dst);
	}
	return (NULL);
}
