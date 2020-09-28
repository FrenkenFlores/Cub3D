/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 15:42:22 by fflores           #+#    #+#             */
/*   Updated: 2020/05/29 23:37:03 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t m)
{
	char	*tmp;
	int		j;
	int		i;

	i = n * m;
	j = 0;
	tmp = (char*)malloc(i);
	if (tmp == NULL)
		return (NULL);
	while (i != 0)
	{
		tmp[j] = '\0';
		j++;
		i--;
	}
	return ((void*)tmp);
}
