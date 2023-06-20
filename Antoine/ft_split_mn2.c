/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mn2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:09:25 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/13 12:09:28 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab_mn(char **tab)
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

void	ft_check_quotes(t_quotes *quote, char *str, int i)
{
	if (str[i] == '\'' && quote->open_d == 0)
		quote->open_s++;
	if (str[i] == '"' && quote->open_s == 0)
		quote->open_d++;
	if (quote->open_s > 1 || quote->open_d > 1)
	{
		quote->open_s = 0;
		quote->open_d = 0;
	}
}

void	ft_get_value_quote(t_quotes *quote)
{
	quote->open_s = 0;
	quote->open_d = 0;
	quote->i = 0;
}

int	ft_count_len(char *str, int c)
{
	t_quotes	quote;
	int			len;

	len = 0;
	ft_get_value_quote(&quote);
	while (str[quote.i] != 0)
	{
		ft_check_quotes(&quote, str, quote.i);
		if (quote.open_s == 0 && quote.open_d == 0)
		{
			if (str[quote.i] == c && str[quote.i + 1] != 0)
				len++;
		}
		quote.i++;
	}
	len++;
	return (len);
}
