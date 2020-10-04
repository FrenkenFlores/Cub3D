/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 10:30:43 by fflores           #+#    #+#             */
/*   Updated: 2020/08/03 10:33:52 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_set_flag(t_flags *flag, char symbol, t_parameters *prmtrs)
{
	if (symbol == '0')
		flag->zero_flag = 1;
	if (symbol == '-')
		flag->negative = 1;
	if (symbol == '.')
		flag->dot = 1;
	if (symbol == '*')
	{
		if ((flag->dot) == 1)
			flag->precision = va_arg(prmtrs->ap, int);
		else
			flag->width = va_arg(prmtrs->ap, int);
	}
	if (symbol >= '1' && symbol <= '9')
	{
		if (flag->dot)
			flag->precision =
				ft_atoi(&(prmtrs->format_copy[prmtrs->count]), prmtrs);
		else
			flag->width =
				ft_atoi(&(prmtrs->format_copy[prmtrs->count]), prmtrs);
	}
	return (0);
}
