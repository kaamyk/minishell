/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:38:42 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/08 17:39:43 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/******************/
/* Create tab cmd */
/******************/

char	*ft_rewritten_strr2(char **tab, char *new_str, int i)
{
	if (i == 0)
		new_str = ft_copy_str(tab[i]);
	else
	{
		new_str = ft_add_string(new_str, " ");
		new_str = ft_add_string(new_str, tab[i]);
	}
	return (new_str);
}

char	*ft_rewritten_strr(t_data *data, char *str)
{
	int		i;
	char	**tab;
	char	*new_str;

	tab = ft_split(str, ' ');
	i = 0;
	while (tab[i])
	{
		tab[i] = ft_delete_space(tab[i]);
		if (tab[i][0] == '\'' || tab[i][0] == '"' || tab[i][0] == '(')
		{
			free(tab[i]);
			tab[i] = ft_copy_str(data->tab_quotes[data->nb_quotes]);
			data->nb_quotes++;
		}
		new_str = ft_rewritten_strr2(tab, new_str, i);
		i++;
	}
	ft_free_tab(tab);
	free(str);
	return (new_str);
}

char	*ft_read_string(t_data *data, char *str)
{
	int		i;
	bool	str_summary;

	str_summary = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"' || str[i] == '(')
		{
			str_summary = true;
			break ;
		}
		i++;
	}
	if (str_summary == true)
		str = (ft_rewritten_strr(data, str));
	return (str);
}

char	**ft_create_tab_cmd(t_data *data, char *str)
{
	int		i;
	char	**tab;

	tab = ft_split(str, ';');
	data->nb_quotes = 0;
	i = 0;
	while (tab[i])
	{
		tab[i] = ft_delete_space(tab[i]);
		tab[i] = ft_read_string(data, tab[i]);
		i++;
	}
	data->nb_cmd = i;
	ft_free_tab(data->tab_quotes);
	free(str);
	return (tab);
}

bool	ft_parsing(t_data *data)
{
	char	*new_str;

	new_str = ft_create_str_without_quotes(data, data->str);
	if (ft_check_syntax_inside(data, new_str) == true)
	{
		free(new_str);
		ft_free_tab(data->tab_quotes);
		free(data->str);
		return (0);
	}
	data->s_bonus = false;
	if (ft_count_len_bonus(new_str) == 0)
	{
		new_str = ft_parsing_mandatory_part2(data, new_str);
		data->tab_cmd = ft_create_tab_cmd(data, new_str);
	}
	else
	{
		data->s_bonus = true;
		ft_parsing_bonus(data, new_str);
	}
	free(data->str);
	return (1);
}
