/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:39:25 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/07 12:40:02 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/********************************/
/* Add ; for ft_split(str, ';') */
/********************************/

char	*ft_combine_str(char **tab)
{
	int		i;
	char	*new_str;

	i = 0;
	while (tab[i])
	{
		if (i == 0)
			new_str = ft_copy_str(tab[i]);
		else
		{
			new_str = ft_add_string(new_str, " ");
			new_str = ft_add_string(new_str, tab[i]);
		}
		i++;
	}
	ft_free_tab(tab);
	return (new_str);
}

char	**ft_create_tab_re(t_data *data, char *str)
{
	int		i;
	char	**tab;
	char	*tmp;

	tab = ft_split(str, ';');
	i = 0;
	while (tab[i])
	{
		tab[i] = ft_delete_space(tab[i]);
		if (tab[i][0] == '>' || tab[i][0] == '<')
		{
			if (ft_nb_c(tab[i], ' ') > 1)
			{
				tmp = tab[i];
				tab[i] = ft_put_cmd_at_first(data, tab[i]);
				free(tmp);
			}
		}
		i++;
	}
	return (tab);
}

/*
[pwd > file | ls] --> [pwd ; > file ; | ls]
*/
int	ft_add_semicolon2(char *str, char *new_str, int i, int m)
{
	if (str[i] == '>' || str[i] == '<')
	{
		if (i > 0 && str[i - 1] != '>' && str[i - 1] != '<')
		{
			new_str[m] = ';';
			m++;
		}
	}
	return (m);
}

char	*ft_add_semicolon(char *str)
{
	int		i;
	int		m;
	int		len;
	char	*new_str;

	len = ft_strlen(str) + ft_count_signe(str);
	new_str = (char *)malloc((len + 1) * sizeof(char));
	if (!new_str)
		return (0);
	i = 0;
	m = 0;
	while (str[i])
	{
		m = ft_add_semicolon2(str, new_str, i, m);
		new_str[m] = str[i];
		m++;
		i++;
	}
	new_str[m] = 0;
	return (new_str);
}

char	*ft_tab_re(t_data *data, char *str)
{
	char	**tab;
	char	*new_str;

	new_str = ft_add_semicolon(str);
	tab = ft_create_tab_re(data, new_str);
	free(new_str);
	new_str = ft_combine_str(tab);
	return (new_str);
}
