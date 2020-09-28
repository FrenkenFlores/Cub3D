/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 18:20:34 by fflores           #+#    #+#             */
/*   Updated: 2020/05/30 00:10:44 by fflores          ###   ########.fr       */
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
	int long	i;
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

void			ft_putnbr_fd(int n, int fd)
{
	int			s;
	int long	i;
	int			k;
	char		c;

	if (fd == -1)
		return ;
	k = 1;
	s = ft_numsize(n);
	while (s != 0)
	{
		if (n < 0 && k == 1)
		{
			write(fd, "-", 1);
			k = -1;
		}
		i = ft_i(s);
		c = '0' + ((n - (n / i) * i) * 10 / i) * k;
		write(fd, &c, 1);
		s--;
	}
}
