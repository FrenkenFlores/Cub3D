/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 10:07:21 by fflores           #+#    #+#             */
/*   Updated: 2020/08/03 10:07:40 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_string(t_parameters prmtrs)
{
	size_t	counter;

	counter = prmtrs.count;
	while (prmtrs.format_copy[++counter] != '\0'
	&& (!(ft_type(prmtrs.format_copy[counter]))))
	{
		if (!(ft_flag_and_digit(prmtrs.format_copy[counter])))
			return (1);
	}
	if (prmtrs.format_copy[counter] == '\0')
		return (1);
	return (0);
}
