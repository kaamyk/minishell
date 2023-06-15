/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:39:19 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/13 13:40:21 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_parsing5(char *str)
{
	t_quotes	quote;
	int			check;

	check = 0;
	ft_get_value_quote(&quote);
	while (str[quote.i] != 0)
	{
		ft_check_quotes(&quote, str, quote.i);
		if (quote.open_s == 0 && quote.open_d == 0)
		{
			if (str[quote.i] == '|'
				|| str[quote.i] == '>'
				|| str[quote.i] == '<')
			{
				if (quote.i == 0
					|| (str[quote.i - 1] != '<' && str[quote.i - 1] != '>'))
					check++;
				if (check > 1)
					break ;
			}
		}
		quote.i++;
	}
	return (ft_new_string(&quote, str));
}

char	*ft_parsing3(char *str)
{
	t_quotes	quote;

	ft_get_value_quote(&quote);
	while (str[quote.i] != 0)
	{
		ft_check_quotes(&quote, str, quote.i);
		if (quote.open_s == 0 && quote.open_d == 0)
		{
			if (str[quote.i] == '|'
				|| str[quote.i] == '>'
				|| str[quote.i] == '<')
				break ;
		}
		quote.i++;
	}
	return (ft_new_string(&quote, str));
}

void	ft_parsing4(t_tab *tab, char *str, int n)
{
	int	i;
	int	m;

	m = 0;
	i = 0;
	while (str[i])
	{
		if (m < tab->nb_signe && i == tab->tab_position[m])
		{
			tab->tab_cmd[n] = ft_parsing5(&str[i]);
			n++;
			m++;
		}
		i++;
	}
	tab->tab_cmd[n] = 0;
	free(tab->tab_position);
}

void	ft_parsing2(t_tab *tab, char *str)
{
	int	n;

	tab->tab_cmd = (char **)malloc((tab->nb_cmd + 1) * sizeof(char *));
	if (!tab->tab_cmd)
		return ;
	n = 0;
	if (str[0] != '>' && str[0] != '<')
	{
		tab->tab_cmd[0] = ft_parsing3(str);
		n++;
	}
	ft_parsing4(tab, str, n);
}

void	ft_parsing(char *str)
{
	t_quotes	quote;
	t_tab		tab;
	int			i;

	tab.tab_position = (int *)malloc(ft_strlen(str) * sizeof(int));
	if (!tab.tab_position)
		return ;
	i = 0;
	tab.nb_cmd = 0;
	tab.nb_signe = 0;
	ft_get_value_quote(&quote);
	while (str[quote.i] != 0)
	{
		ft_check_quotes(&quote, str, quote.i);
		i = ft_without_quotes2(&quote, &tab, str, i);
		quote.i++;
	}
	if (str[0] != '|'
		&& str[0] != '<'
		&& str[0] != '>')
		tab.nb_cmd++;
	ft_parsing2(&tab, str);
	ft_parsing6(&tab);
}
