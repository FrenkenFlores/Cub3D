/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 10:05:25 by fflores           #+#    #+#             */
/*   Updated: 2020/08/03 10:05:50 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_ch(t_flags flag, t_parameters *prmtrs)
{
	int		ch;
	char	*ptr;

	ch = va_arg(prmtrs->ap, int);
	ptr = ft_char(ch);
	if (ptr == NULL)
		return (NULL);
	if (flag.width)
		if (!(ptr = ft_apply_width(flag.width - 1 + ft_strlen(ptr), ptr, ' ')))
			return (NULL);
	if (flag.negative)
		if (!(ptr = ft_align_left_side(ptr)))
			return (NULL);
	if (ch == 0)
	{
		if (flag.negative)
			prmtrs->head_zero = 1;
		else
			prmtrs->back_zero = 1;
	}
	return (ptr);
}

char	*ft_char(int c)
{
	char	*s;

	s = (char *)malloc(sizeof(char) * 2);
	if (!s)
		return (NULL);
	s[0] = (char)c;
	s[1] = '\0';
	return (s);
}
