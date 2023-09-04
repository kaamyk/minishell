/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:09:14 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/13 12:09:17 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_copy_with_quotes(char *str, char c_open)
{
	int		i;
	int		nb_quote;
	char	c_close;
	char	*new_str;

	if (c_open == '(')
		c_close = ')';
	else
		c_close = c_open;
	new_str = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!new_str)
		return (0);
	nb_quote = 0;
	i = 0;
	while (str[i])
	{
		if (nb_quote == 2 && str[i] == ' ')
			break ;
		if (str[i] == c_open || str[i] == c_close)
			nb_quote++;
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}

char	*ft_copy_without_quotes(char *str)
{
	int		i;
	int		len;
	char	*new_str;

	len = 0;
	while (str[len])
		len++;
	new_str = (char *)malloc((len + 1) * sizeof(char));
	if (!new_str)
		return (0);
	i = 0;
	while (i < len)
	{
		if (str[i] == ' ')
			break ;
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}

char	**ft_create_tab(char **tab, char *str)
{
	int		i;
	int		p;
	char	c;

	p = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			if (i == 0 || str[i - 1] == ' ')
			{
				c = ft_check_quotes_in_str(&str[i]);
				if (c == '\'' || c == '"' || c == '(')
					tab[p] = ft_copy_with_quotes(&str[i], c);
				else
					tab[p] = ft_copy_without_quotes(&str[i]);
				i += ft_strlen(tab[p]) - 1;
				p++;
			}
		}
		i++;
	}
	tab[p] = 0;
	return (tab);
}

char	**ft_split_mn(char *str, char c)
{
	int		len;
	int		i;
	char	**tab;

	(void)c;
	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			if (i == 0 || str[i - 1] == ' ')
				len++;
		}
		i++;
	}
	tab = (char **)malloc((len + 1) * sizeof(char *));
	if (!tab)
		return (0);
	tab = ft_create_tab(tab, str);
	return (tab);
}
