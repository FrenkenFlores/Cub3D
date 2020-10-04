/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 00:45:20 by fflores           #+#    #+#             */
/*   Updated: 2020/05/23 22:47:09 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char *pointer;

	pointer = (char*)s;
	if (s || c == 0)
	{
		while (*pointer != '\0')
		{
			if (*pointer == c)
				return (pointer);
			pointer++;
		}
		if (*pointer == '\0' && c == '\0')
			return (pointer);
	}
	return (NULL);
}
