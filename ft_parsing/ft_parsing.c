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

void	ft_return_value_in_quote(t_data *data, char *new_str, int *m)
{
	int	i;

	i = 0;
	while (data->tab_quotes[data->nb_quotes][i])
	{
		new_str[*m] = data->tab_quotes[data->nb_quotes][i];
		(*m)++;
		i++;
	}
	data->nb_quotes++;
}

char	*ft_read_string(t_data *data, char *str)
{
	int		i;
	int		m;
	char	*new_str;

	new_str = (char *)malloc(255 * sizeof(char));
	if (!new_str)
		return (0);
	i = 0;
	m = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			ft_return_value_in_quote(data, new_str, &m);
		else
		{
			new_str[m] = str[i];
			m++;
		}
		i++;
	}
	new_str[m] = 0;
	free(str);
	return (new_str);
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
	tab = ft_change_file_direc(tab);
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
