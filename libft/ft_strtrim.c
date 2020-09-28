/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 19:15:29 by fflores           #+#    #+#             */
/*   Updated: 2020/05/29 17:14:41 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(char const *s1)
{
	int i;

	i = 0;
	while (*s1++ != '\0')
		i++;
	return (i);
}

static int	ft_lnoise(char const *set, char s1)
{
	while (*set != '\0')
	{
		if (*set == s1)
			return (1);
		set++;
	}
	return (0);
}

static int	ft_rnoise(char const *s1, char const *set, int len)
{
	int i;
	int j;
	int k;

	j = 0;
	i = 1;
	k = 0;
	while (*s1 != s1[len - k])
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (set[j] == s1[len - i])
				i++;
			j++;
		}
		k++;
	}
	if (i > 1)
		return (len - i + 1);
	return (len);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char		*s2;
	char		*s3;
	int			end;

	if (!s1 || !set)
		return ("\0");
	while (ft_lnoise(set, *s1))
		s1++;
	end = ft_rnoise(s1, set, ft_len(s1));
	s2 = (char*)malloc(end + 1);
	if (s2 == NULL)
		return (NULL);
	s3 = s2;
	while (end != 0)
	{
		*s2++ = *s1++;
		end--;
	}
	*s2 = '\0';
	return (s3);
}
