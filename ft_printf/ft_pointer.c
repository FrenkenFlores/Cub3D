/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 10:23:23 by fflores           #+#    #+#             */
/*   Updated: 2020/08/03 10:23:32 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*ft_0x(char *string)
{
	char *str;

	if (!(str = ft_strjoin("0x", string)))
		return (NULL);
	free(string);
	return (str);
}

static char		*ft_pointer_precision(t_flags flag, char *ptr)
{
	if (!(ptr = ft_apply_width(flag.precision, ptr, '0')))
		return (NULL);
	if (!(ptr = ft_0x(ptr)))
		return (NULL);
	if (flag.width)
		if (!(ptr = ft_apply_width(flag.width, ptr, ' ')))
			return (NULL);
	if (flag.negative)
		if (!(ptr = ft_align_left_side(ptr)))
			return (NULL);
	return (ptr);
}

static char		*ft_pointer_without_precision(t_flags flag, char *ptr)
{
	if (flag.negative)
	{
		if (!(ptr = ft_0x(ptr)))
			return (NULL);
		return (ft_apply_rightwidth(flag.width, ptr, ' '));
	}
	if (!flag.zero_flag)
	{
		if (!(ptr = ft_0x(ptr)))
			return (NULL);
		if (!(ptr = ft_apply_width(flag.width, ptr, ' ')))
			return (NULL);
	}
	if (flag.zero_flag)
	{
		if (!(ptr = ft_apply_width(flag.width - 2, ptr, '0')))
			return (NULL);
		if (!(ptr = ft_0x(ptr)))
			return (NULL);
	}
	return (ptr);
}

char			*ft_pointer(t_flags flag, t_parameters *prmtrs)
{
	char	*ptr;
	void	*p;

	p = va_arg(prmtrs->ap, void *);
	if (p)
	{
		if (!(ptr = ft_hex_itoa((unsigned long long)p)))
			return (NULL);
	}
	else
	{
		if (!(ptr = ft_strdup("0")))
			return (NULL);
	}
	if (flag.dot)
		if (!(ptr = ft_pointer_precision(flag, ptr)))
			return (NULL);
	if (!flag.dot)
		if (!(ptr = ft_pointer_without_precision(flag, ptr)))
			return (NULL);
	return (ptr);
}
