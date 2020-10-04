/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 14:30:57 by fflores           #+#    #+#             */
/*   Updated: 2020/05/29 22:33:04 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_numsize(int n)
{
	int i;
	int j;

	i = 0;
	j = n;
	if (n == 0)
		return (1);
	while (j != 0)
	{
		j = j / 10;
		i++;
	}
	return (i);
}

static long	int	ft_i(int size)
{
	long int	i;
	int			j;

	i = 1;
	j = 0;
	while (j != size)
	{
		i = i * 10;
		j++;
	}
	return (i);
}

static char		*ft_maloc(int size, int n)
{
	if (n < 0)
		return ((char*)malloc(sizeof(char) * size + 2));
	return ((char*)malloc(sizeof(char) * size + 1));
}

char			*ft_itoa(int n)
{
	char		*tmp;
	char		*str;
	int			size;
	int long	i;
	int			k;

	k = 1;
	size = ft_numsize(n) + 1;
	str = ft_maloc((size - 1), n);
	if (!str)
		return (0);
	tmp = str;
	while (--size != 0 && str)
	{
		if (n < 0 && k > 0)
		{
			*tmp++ = '-';
			k = -1;
		}
		i = ft_i(size);
		*tmp = '0' + ((n - (n / i) * i) * 10 / i) * k;
		tmp++;
	}
	*tmp = '\0';
	return (str);
}
