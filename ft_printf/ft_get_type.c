/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 10:11:58 by fflores           #+#    #+#             */
/*   Updated: 2020/08/03 10:12:10 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_get_type(t_flags flag, t_parameters *prmtrs)
{
	char *ptr;

	prmtrs->line = prmtrs->format_copy[prmtrs->count];
	if (prmtrs->format_copy[prmtrs->count] == '%')
		return (ft_percent(flag));
	if (prmtrs->format_copy[prmtrs->count] == 'c')
		return (ft_ch(flag, prmtrs));
	if (prmtrs->format_copy[prmtrs->count] == 's')
		return (ft_str(flag, prmtrs));
	if (prmtrs->format_copy[prmtrs->count] == 'x')
		return (ft_hex_trunc(flag, prmtrs));
	if (prmtrs->format_copy[prmtrs->count] == 'X')
	{
		if (!(ptr = ft_hex_trunc(flag, prmtrs)))
			return (NULL);
		return (ft_hex_full(ptr));
	}
	if (prmtrs->format_copy[prmtrs->count] == 'd' ||
		prmtrs->format_copy[prmtrs->count] == 'i')
		return (ft_int_decimal(flag, prmtrs));
	if (prmtrs->format_copy[prmtrs->count] == 'u')
		return (ft_unsigned(flag, prmtrs));
	if (prmtrs->format_copy[prmtrs->count] == 'p')
		return (ft_pointer(flag, prmtrs));
	return (NULL);
}
