/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:44:59 by xuluu             #+#    #+#             */
/*   Updated: 2022/11/23 17:01:30 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i] != 0)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*cpy_str(char *str, size_t i, char const *s, char c)
{
	size_t	m;

	m = 0;
	while (s[i] != c && s[i] != 0)
	{
		str[m] = s[i];
		m++;
		i++;
	}
	str[m] = 0;
	return (str);
}

char	*create_str(char **tab, size_t i, char const *s, char c)
{
	size_t	n;
	size_t	len;
	char	*str;

	n = i;
	len = 0;
	while (s[n] != c && s[n] != 0)
	{
		len++;
		n++;
	}
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
	{
		free_tab(tab);
		return (0);
	}
	return (cpy_str(str, i, s, c));
}

char	**create_tab(char **tab, char const *s, char c, size_t len)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (s[i] != 0)
	{
		if (k == len)
			break ;
		while (s[i] == c)
			i++;
		if (k < len)
		{
			tab[k] = create_str(tab, i, s, c);
			while (s[i] != c && s[i] != 0)
				i++;
			while (s[i] == c)
				i++;
		}
		k++;
	}
	tab[k] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	len;
	size_t	i;
	size_t	n;

	if (!s)
		return (0);
	i = 0;
	len = 0;
	while (s[i] != 0)
	{
		n = i;
		while (s[i] != c && s[i] != 0)
			i++;
		if (n == i)
			i++;
		else
			len++;
	}
	tab = (char **)malloc((len + 1) * sizeof(char *));
	if (!tab)
		return (0);
	return (create_tab(tab, s, c, len));
}
