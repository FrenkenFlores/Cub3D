/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 10:38:14 by fflores           #+#    #+#             */
/*   Updated: 2020/08/03 10:38:21 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*ft_itoa_for_unsigned(unsigned long long number)
{
	int		length;
	char	str[11];
	int		i;
	int		j;
	char	*string;

	i = 0;
	j = -1;
	if (number == 0)
		return (ft_strdup("0"));
	while (number != 0)
	{
		str[i++] = (char)(number % 10 + 48);
		number /= 10;
	}
	str[i] = '\0';
	length = ft_strlen(str);
	if (!(string = (char *)malloc((length + 1) * sizeof(char))))
		return (NULL);
	while (++j < length)
		string[j] = str[length - j - 1];
	string[j] = '\0';
	return (string);
}

static char		*ft_precision_unsigned(t_flags flag, char *ptr)
{
	if (flag.precision == 0 && ptr[0] == '0')
		ptr[0] = '\0';
	else
	{
		if (!(ptr = ft_apply_width(flag.precision, ptr, '0')))
			return (NULL);
	}
	if (!(ptr = ft_apply_width(flag.precision, ptr, '0')))
		return (NULL);
	if (flag.width)
		if (!(ptr = ft_apply_width(flag.width, ptr, ' ')))
			return (NULL);
	if (flag.negative)
		if (!(ptr = ft_align_left_side(ptr)))
			return (NULL);
	return (ptr);
}

char			*ft_unsigned(t_flags flag, t_parameters *prmtrs)
{
	char			*ptr;
	unsigned int	p;

	p = va_arg(prmtrs->ap, unsigned int);
	ptr = ft_itoa_for_unsigned(p);
	if (flag.dot)
	{
		if (!(ptr = ft_precision_unsigned(flag, ptr)))
			return (NULL);
		if (flag.negative)
			return (ft_apply_rightwidth(flag.width, ptr, ' '));
	}
	else
	{
		if (flag.zero_flag)
			if (!(ptr = ft_apply_width(flag.width, ptr, '0')))
				return (NULL);
		if (flag.negative)
			return (ft_apply_rightwidth(flag.width, ptr, ' '));
		if (flag.width)
			if (!(ptr = ft_apply_width(flag.width, ptr, ' ')))
				return (NULL);
	}
	return (ptr);
}
