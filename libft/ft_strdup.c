/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 18:42:29 by fflores           #+#    #+#             */
/*   Updated: 2020/05/30 00:17:15 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(const char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
		i++;
	return (i);
}

static void	ft_cpy(const char *dst, const char *src)
{
	while (*src != '\0')
		*((char*)dst++) = *((char*)src++);
	*((char*)dst) = '\0';
}

char		*ft_strdup(const char *src)
{
	char *dup;

	dup = (char*)malloc(ft_len(src) + 1);
	if (dup == NULL)
		return (NULL);
	ft_cpy(dup, src);
	return (dup);
}
