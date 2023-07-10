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

char	*create_str_mn(char **tab, char *str, int len, int i)
{
	char		*cmd;
	int			m;

	cmd = (char *)malloc((len - i + 1) * sizeof(char));
	if (!cmd)
	{
		free_tab_mn(tab);
		return (0);
	}
	m = 0;
	while (str[i] != 0 && i < len)
	{
		cmd[m] = str[i];
		i++;
		m++;
	}
	cmd[m] = 0;
	return (cmd);
}

void	ft_without_quotes3(t_quotes *quote,
	t_split *sp_tab, char **tab, char *str)
{
	if (quote->open_s == 0 && quote->open_d == 0)
	{
		if (str[quote->i] == sp_tab->c && str[quote->i + 1] != 0)
		{
			tab[sp_tab->p] = create_str_mn(tab, str, quote->i, sp_tab->start);
			sp_tab->start += (ft_strlen(tab[sp_tab->p]) + 1);
			tab[sp_tab->p] = ft_delete_space(tab[sp_tab->p]);
			sp_tab->p++;
		}
	}
}

char	**create_tab_mn(char **tab, char *str, char c)
{
	t_quotes	quote;
	t_split		sp_tab;

	sp_tab.start = 0;
	sp_tab.p = 0;
	sp_tab.c = c;
	ft_get_value_quote(&quote);
	while (str[quote.i] != 0)
	{
		ft_check_quotes(&quote, str, quote.i);
		ft_without_quotes3(&quote, &sp_tab, tab, str);
		quote.i++;
	}
	if (str[quote.i - 1] == c)
		quote.i--;
	tab[sp_tab.p] = create_str_mn(tab, str, quote.i, sp_tab.start);
	tab[sp_tab.p] = ft_delete_space(tab[sp_tab.p]);
	tab[sp_tab.p + 1] = 0;
	return (tab);
}

char	**ft_split_mn(char *str, char c)
{
	char	**tab;
	int		len;

	len = ft_count_len(str, c);
	tab = (char **)malloc((len + 1) * sizeof(char *));
	if (!tab)
		return (0);
	tab = create_tab_mn(tab, str, c);
	return (tab);
}
