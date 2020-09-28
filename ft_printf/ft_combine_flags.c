/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_combine_flags.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 10:08:12 by fflores           #+#    #+#             */
/*   Updated: 2020/08/03 10:08:28 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_combine_flags(t_flags *flag)
{
	if (flag->negative)
		flag->zero_flag = 0;
	if (flag->width < 0)
	{
		flag->negative = 1;
		flag->width *= -1;
	}
	if (flag->precision < 0)
		flag->dot = 0;
}
