/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_parameters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 10:06:21 by fflores           #+#    #+#             */
/*   Updated: 2020/08/03 10:06:38 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_parameters(t_parameters *prmtrs)
{
	t_flags	flag;
	char	*string;

	ft_start(&flag, prmtrs);
	if (ft_check_string(*prmtrs))
		return (1);
	while (prmtrs->format_copy[++(prmtrs->count)] != '\0' &&
		ft_flag_and_digit(prmtrs->format_copy[prmtrs->count]))
		ft_set_flag(&flag, prmtrs->format_copy[prmtrs->count], prmtrs);
	ft_combine_flags(&flag);
	if (!(string = ft_get_type(flag, prmtrs)))
		return (1);
	else
	{
		ft_null_str(string, prmtrs);
		prmtrs->length += ft_strlen(string);
		free(string);
	}
	return (0);
}
