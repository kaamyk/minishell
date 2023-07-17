/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:13:41 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/07 11:15:15 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/****************************/
/* Rewrite the command line */
/****************************/

char	*ft_change_redirection(t_data *data, char *str)
{
	char	*tmp;
	int		nb_signe;
	int		i;

	nb_signe = ft_count_signe(str);
	i = 0;
	while (i < nb_signe)
	{
		tmp = str;
		str = ft_tab_re(data, str);
		free(tmp);
		i++;
	}
	str = ft_put_reout_at_first(data, str);
	str = ft_put_file_direction(str);
	return (str);
}

/*
tab pipe
*/
char	*ft_tab_pp(t_data *data, char **tab)
{
	int		i;
	char	*new_str;

	i = 0;
	while (tab[i])
	{
		tab[i] = ft_delete_space(tab[i]);
		if (ft_find_c(tab[i], '>') == true
			|| ft_find_c(tab[i], '<') == true)
			tab[i] = ft_change_redirection(data, tab[i]);
		if (i == 0)
			new_str = ft_copy_str(tab[i]);
		else
		{
			if (tab[i][0] == '>' || tab[i][0] == '<')
				new_str = ft_add_string(new_str, " ; | ; ");
			else
				new_str = ft_add_string(new_str, " ; | ");
			new_str = ft_add_string(new_str, tab[i]);
		}
		i++;
	}
	ft_free_tab(tab);
	return (new_str);
}

char	*ft_parsing_mandatory_part2(t_data *data, char *str)
{
	char	**tab_pp;
	char	*tmp;

	data->s_pipe = false;
	if (ft_find_c(str, '|') == true)
	{
		data->s_pipe = true;
		tab_pp = ft_split(str, '|');
		tmp = str;
		str = ft_tab_pp(data, tab_pp);
		free(tmp);
	}
	else if (ft_find_c(str, '>') == true
		|| ft_find_c(str, '<') == true)
	{
		str = ft_change_redirection(data, str);
	}
	return (str);
}
