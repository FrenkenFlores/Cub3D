/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 10:24:25 by fflores           #+#    #+#             */
/*   Updated: 2020/08/03 10:24:43 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	t_parameters	param;

	param.length = 0;
	param.count = 0;
	param.format_copy = format;
	va_start(param.ap, format);
	while (param.format_copy[param.count] != '\0')
	{
		if (param.format_copy[param.count] == '%')
		{
			if (ft_check_parameters(&param))
			{
				ft_putchar(param.format_copy[param.count]);
				param.length++;
			}
		}
		else
		{
			ft_putchar(param.format_copy[param.count]);
			param.length++;
		}
		(param.count)++;
	}
	va_end(param.ap);
	return (param.length);
}
