/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 10:34:14 by fflores           #+#    #+#             */
/*   Updated: 2020/08/03 10:34:24 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_start(t_flags *flag, t_parameters *prmtrs)
{
	prmtrs->head_zero = 0;
	prmtrs->back_zero = 0;
	flag->dot = 0;
	flag->negative = 0;
	flag->width = 0;
	flag->zero_flag = 0;
	flag->precision = 0;
}
