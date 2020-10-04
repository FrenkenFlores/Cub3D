/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <fflores@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 11:45:51 by fflores           #+#    #+#             */
/*   Updated: 2020/08/11 11:09:54 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					get_next_line(int fd, char **line)
{
	char			buf[BUFFER_SIZE + 1];
	char			*pointer;
	static char		*tmp;
	int				count;

	count = 0;
	pointer = NULL;
	if (line == NULL || fd < 0)
		return (-1);
	tmp = check_tmp(&tmp, line, &count);
	while (!(tmp) && (count = read(fd, buf, BUFFER_SIZE)))
	{
		if (count < 0)
			return (-1);
		buf[count] = '\0';
		if ((pointer = ft_strchr(buf, '\n')))
		{
			*pointer = '\0';
			tmp = ft_strdup(++pointer);
		}
		*line = gnl_strjoin(*line, buf);
	}
	if (tmp && count == 0)
		free(tmp);
	return ((count ? 1 : 0));
}
