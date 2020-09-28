/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 10:13:46 by fflores           #+#    #+#             */
/*   Updated: 2020/08/03 10:14:13 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_apply_width(size_t counter, char *string, char ch)
{
	char	*str;
	size_t	i;

	i = 0;
	if (ft_strlen(string) >= counter)
		return (string);
	if (!(str = malloc((counter + 1) * sizeof(char))))
		return (NULL);
	while (i++ < counter)
		str[i - 1] = ch;
	str[counter] = '\0';
	i = ft_strlen(string);
	while (i-- > 0)
		str[--counter] = string[i];
	free(string);
	return (str);
}

char	*ft_align_left_side(char *ptr)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (ptr[i] != '\0' && ptr[i] == ' ')
		i++;
	if (ptr[i] == '\0' || !i)
		return (ptr);
	while (ptr[i] != '\0')
		ptr[counter++] = ptr[i++];
	while ((ptr[counter] != '\0'))
		ptr[counter++] = ' ';
	return (ptr);
}

char	*ft_apply_rightwidth(size_t counter, char *string, char ch)
{
	char	*str;
	size_t	i;

	i = 0;
	if (ft_strlen(string) >= counter)
		return (string);
	if (!(str = malloc((counter + 1) * sizeof(char))))
		return (NULL);
	while (i++ < counter)
		str[i - 1] = ch;
	str[counter] = '\0';
	i = ft_strlen(string);
	while (i-- > 0)
		str[i] = string[i];
	free(string);
	return (str);
}
