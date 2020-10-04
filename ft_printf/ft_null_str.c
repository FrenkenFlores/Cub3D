/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_null_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 10:20:37 by fflores           #+#    #+#             */
/*   Updated: 2020/08/03 10:22:12 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_null_str(char *str, t_parameters *prmtrs)
{
	char zero;

	zero = '\0';
	if (prmtrs->head_zero)
	{
		write(1, &zero, 1);
		prmtrs->length++;
	}
	if (str)
	{
		while (*str)
		{
			write(1, str, 1);
			str++;
		}
	}
	if (prmtrs->back_zero)
	{
		write(1, &zero, 1);
		prmtrs->length++;
	}
}
