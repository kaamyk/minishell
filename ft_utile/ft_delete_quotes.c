/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:12:11 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/24 13:12:36 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_find_poisition_quote(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

void	ft_delete_quotes(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (ft_find_poisition_quote(tab[i], '\'')
			< ft_find_poisition_quote(tab[i], '"')
			&& ft_find_poisition_quote(tab[i], '\'') != (int)ft_strlen(tab[i]))
			tab[i] = del_char(tab[i], '\'');
		else if (ft_find_poisition_quote(tab[i], '\'')
			> ft_find_poisition_quote(tab[i], '"')
			&& ft_find_poisition_quote(tab[i], '"') != (int)ft_strlen(tab[i]))
			tab[i] = del_char(tab[i], '"');
		i++;
	}
}
