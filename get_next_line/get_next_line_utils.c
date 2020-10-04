/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <fflores@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 15:51:35 by fflores           #+#    #+#             */
/*   Updated: 2020/08/11 11:28:47 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*check_tmp(char **tmp, char **line, int *count)
{
	char *pointer;

	pointer = NULL;
	if (*tmp)
	{
		*count = 1;
		if ((pointer = ft_strchr(*tmp, '\n')))
		{
			*pointer = '\0';
			if (ft_len(*line) > BUFFER_SIZE && ft_len(*tmp) != 0)
				free(*line);
			*line = ft_strdup(*tmp);
			pointer = ft_strdup(++pointer);
		}
		else
			*line = ft_strdup(*tmp);
		free(*tmp);
	}
	else
		*line = ft_strdup("");
	return (pointer);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char *s3;
	char *s4;
	char *clear;

	if (!s1 || !s2)
		return ("\0");
	clear = s1;
	s3 = (char*)malloc((ft_len(s1) + ft_len(s2) + 1) * sizeof(char));
	if (s3 == NULL)
		return (NULL);
	s4 = s3;
	while (*s1 != '\0')
		*s3++ = *s1++;
	while (*s2 != '\0')
		*s3++ = *s2++;
	*s3 = '\0';
	free(clear);
	return (s4);
}

size_t	ft_len(const char *s)
{
	size_t i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	char *dst;
	char *str;

	if (!src)
		return (NULL);
	if (!(dst = (char*)malloc((ft_len(src) + 1) * sizeof(char))))
		return (NULL);
	str = dst;
	while (*src != '\0')
		*((char*)dst++) = *((char*)src++);
	*((char*)dst) = '\0';
	return (str);
}

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
