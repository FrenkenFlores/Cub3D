/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <fflores@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 15:54:23 by fflores           #+#    #+#             */
/*   Updated: 2020/08/11 10:33:26 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 42
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

int		get_next_line(int fd, char **line);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_len(const char *s);
char	*ft_strdup(const char *src);
char	*gnl_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*check_tmp(char **tmp, char **line, int *count);

#endif
