/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_full.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 10:14:54 by fflores           #+#    #+#             */
/*   Updated: 2020/08/03 10:15:39 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c + 65 - 97);
	return (c);
}

char		*ft_hex_full(char *string)
{
	int i;

	i = -1;
	while (string[++i] != '\0')
		string[i] = (char)ft_toupper(string[i]);
	return (string);
}
