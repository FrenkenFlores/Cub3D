/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_decimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 10:18:25 by fflores           #+#    #+#             */
/*   Updated: 2020/08/03 10:18:40 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ft_int_decimal(t_flags flag, t_parameters *prmtrs)
{
	char	*ptr;
	long	p;
	int		sign;

	sign = 1;
	p = (long)va_arg(prmtrs->ap, int);
	if (p < 0)
	{
		sign = -1;
		p = p * (-1);
	}
	ptr = ft_itoa(p);
	if (flag.dot)
		if (!(ptr = ft_precision_integer(sign, flag, ptr)))
			return (NULL);
	if (!flag.dot)
		if (!(ptr = ft_without_precision(sign, flag, ptr)))
			return (NULL);
	return (ptr);
}

static char		*negative(char *string)
{
	int		length;
	int		i;
	char	*line;

	length = ft_strlen(string);
	i = -1;
	if (!(line = malloc((length + 1) * sizeof(char))))
		return (NULL);
	while (++i < length)
		line[i] = string[length - i - 1];
	line[i] = '\0';
	return (line);
}

char			*ft_itoa(long number)
{
	char	str[11];
	int		znak;
	int		i;

	znak = (number < 0) ? -1 : 1;
	i = 0;
	if (number == 0)
		return (ft_strdup("0"));
	if (number == -2147483648)
		return (ft_strdup("-2147483648"));
	number = (number < 0) ? (number * znak) : number;
	while (number)
	{
		str[i++] = (char)(number % 10 + 48);
		number /= 10;
	}
	if (znak == -1)
		str[i++] = '-';
	str[i] = '\0';
	return (negative(str));
}
