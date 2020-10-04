/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 02:53:47 by fflores           #+#    #+#             */
/*   Updated: 2020/06/01 11:20:13 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(char const *s, char c)
{
	int i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i + 1);
}

static int	ft_spnum(char const *s, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	while (s[i] == c && s[i + 1] == c)
		i++;
	if (s[i + 1] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		i++;
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			j++;
	}
	if (i == j + 1)
		return (0);
	return (j + 2);
}

static void	ft_maloc(char **mas, char const *s, char c)
{
	int k;
	int j;
	int i;

	k = ft_spnum(s, c);
	j = 0;
	while (k != j && *s != '\0')
	{
		i = 0;
		while (*s == c && *s != '\0')
			s++;
		mas[j] = (char*)malloc(ft_len(s, c) * sizeof(char));
		if (mas[j] == NULL)
			while (j != 0)
			{
				free(mas[j]);
				j--;
			}
		while (*s != c && *s != '\0')
			mas[j][i++] = *s++;
		mas[j++][i] = '\0';
		while (*s == c && *s != '\0')
			s++;
	}
	mas[j] = NULL;
}

char		**ft_split(char const *s, char c)
{
	char	**mas;

	mas = (char**)malloc(ft_spnum(s, c) * sizeof(char*));
	if (!mas)
		return (NULL);
	ft_maloc(mas, s, c);
	return (mas);
}
