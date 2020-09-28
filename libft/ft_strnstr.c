/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 04:32:13 by fflores           #+#    #+#             */
/*   Updated: 2020/06/02 10:50:39 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (!*little)
		return ((char*)big);
	while (i < len && big[i] != '\0')
	{
		if (big[i] == little[0])
		{
			while (little[j] != '\0' && big[i + j] == little[j] && i + j < len)
			{
				if (little[j + 1] == '\0')
					return ((char*)&big[i]);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
