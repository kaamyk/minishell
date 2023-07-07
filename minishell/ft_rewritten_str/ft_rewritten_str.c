/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rewritten_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:12:51 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/07 10:33:31 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_find_character(char *str, char c)
{
	t_quotes	quote;

	ft_get_value_quote(&quote);
	while (str[quote.i] != 0)
	{
		ft_check_quotes(&quote, str, quote.i);
		if (quote.open_s == 0 && quote.open_d == 0)
		{
			if (str[quote.i] == c)
				return (true);
		}
		quote.i++;
	}
	return (false);
}

char	*ft_add_string(char *s1, char *s2)
{
	char	*tmp;

	tmp = s1;
	s1 = ft_strjoin(s1, s2);
	free(tmp);
	return (s1);
}

char	*ft_rewritten_with_pipe(char **tab)
{
	char	*str;
	int		i;

	i = 0;
	while (tab[i] != 0)
	{
		if (ft_find_character(tab[i], '>') == true
			|| ft_find_character(tab[i], '<') == true)
			tab[i] = ft_rewritten_with_redirection(tab[i]);
		tab[i] = ft_delete_space(tab[i]);
		if (i == 0)
			str = ft_copy_str(tab[i]);
		else
		{
			str = ft_add_string(str, " | ");
			str = ft_add_string(str, tab[i]);
		}
		free(tab[i]);
		i++;
	}
	free(tab);
	return (str);
}

char	*ft_rewritten_with_dollar(char **tab)
{
	char	*str;
	int		i;

	i = 0;
	while (tab[i] != 0)
	{
		if (i == 0)
		{
			if (tab[i][0] != '(')
				str = ft_copy_str("$");
			str = ft_copy_str(tab[i]);
		}
		else
		{
			str = ft_add_string(str, " ");
			if (tab[i][0] != '(')
				str = ft_add_string(str, " $");
			str = ft_add_string(str, tab[i]);
		}
		free(tab[i]);
		i++;
	}
	free(tab);
	return (str);
}

void	ft_rewritten_str(t_data *data)
{
	char	**tab;
	char	*tmp;

	if (ft_find_character(data->str, '|') == true)
	{
		tab = ft_split_mn(data->str, '|');
		tmp = data->str;
		data->str = ft_rewritten_with_pipe(tab);
		free(tmp);
	}
	else if (ft_find_character(data->str, '>') == true
		|| ft_find_character(data->str, '<') == true)
		data->str = ft_rewritten_with_redirection(data->str);
	if (ft_find_character(data->str, '$') == true)
	{
		tab = ft_split_mn(data->str, '$');
		tmp = data->str;
		data->str = ft_rewritten_with_dollar(tab);
		free(tmp);
	}
	data->str = ft_delete_space(data->str);
}
