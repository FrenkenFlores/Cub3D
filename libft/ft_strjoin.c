/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 18:35:32 by fflores           #+#    #+#             */
/*   Updated: 2020/05/29 17:14:56 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sumlen(char const *s1, char const *s2)
{
	int i;

	i = 0;
	while (*s1++ != '\0')
		i++;
	while (*s2++ != '\0')
		i++;
	return (i);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char *s3;
	char *s4;

	if (!s1 || !s2)
		return ("\0");
	s3 = (char*)malloc(ft_sumlen(s1, s2) + 1);
	if (s3 == NULL)
		return (NULL);
	s4 = s3;
	while (*s1 != '\0')
		*s3++ = *s1++;
	while (*s2 != '\0')
		*s3++ = *s2++;
	*s3 = '\0';
	return (s4);
}
