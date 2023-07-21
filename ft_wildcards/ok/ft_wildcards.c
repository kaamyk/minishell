/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:47:13 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/17 12:47:16 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_env	*g_env;

bool	ft_find(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (s2[i] == 0)
		return (1);
	return (0);
}

char	*ft_determine_the_path(t_data *data, char *str)
{
	int		len;
	char	*list_fd;

	list_fd = ft_get_current_directory(data);
	len = ft_strlen(str);
	if (len > 1)
	{
		if (str[0] == '*' && str[len - 1] == '*')
			list_fd = ft_find_center(str, list_fd);
		else if (str[0] != '*' && str[len - 1] == '*')
			list_fd = ft_find_first(str, list_fd);
		else if (str[0] == '*' && str[len - 1] != '*')
			list_fd = ft_find_end(str, list_fd);
		else
			list_fd = ft_wildcards_is_center(str, list_fd);
	}
	if (list_fd)
	{
		free(str);
		return (list_fd);
	}
	return (str);
}

char	*ft_delete_new_line(char *str)
{
	int		i;
	char	*new_str;
	char	**tab;

	tab = ft_split(str, '\n');
	i = 0;
	while (tab[i])
	{
		new_str = ft_rewritten_strr2(tab, new_str, i);
		i++;
	}
	ft_free_tab(tab);
	free(str);
	return (new_str);
}

void	ft_wildcards2(t_data *data, char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		tab[i] = ft_delete_space(tab[i]);
		if (ft_find_c(tab[i], '*') == true)
		{
			tab[i] = ft_one_wildcard(tab[i]);
			tab[i] = ft_determine_the_path(data, tab[i]);
			tab[i] = ft_delete_new_line(tab[i]);
		}
		else
			tab[i] = ft_read_string(data, tab[i]);
		data->str_with_wildcard = ft_rewritten_strr2
			(tab, data->str_with_wildcard, i);
		i++;
	}
}

char	*ft_wildcards(t_data *data, char *str)
{
	char	*new_str;
	char	**tab;

	if (ft_find_c(str, '*') == true && ft_find_c(str, ' ') == true)
	{
		data->nb_quotes = 0;
		data->tab_quotes = (char **)malloc
			((ft_strlen(str) + 1) * sizeof(char *));
		if (!data->tab_quotes)
			return (0);
		new_str = ft_create_string_summary(data, str);
		tab = ft_split(new_str, ' ');
		free(new_str);
		data->nb_quotes = 0;
		data->tab_wildcards = tab;
		ft_wildcards2(data, tab);
		ft_free_tab(tab);
		ft_free_tab(data->tab_quotes);
		free(str);
		return (data->str_with_wildcard);
	}
	return (str);
}
