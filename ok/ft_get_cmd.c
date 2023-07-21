/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:52:04 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/10 15:34:34 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**********************************/
/* Create [data->cmd] [data->arg] */
/**********************************/

char	*ft_cmd_with_path(char *str)
{
	int		i;
	char	*tmp;

	if (ft_strnstr(str, PATH, 5) != 0)
	{
		i = 0;
		while (i < 5)
			i++;
		if (str[i])
		{
			tmp = str;
			str = ft_copy_str(&str[i]);
			free(tmp);
		}
	}
	return (str);
}

char	*ft_create_arg(char **tab, char *new_str, int i)
{
	if (i == 1)
		new_str = ft_copy_str(tab[i]);
	else
	{
		new_str = ft_add_string(new_str, " ");
		new_str = ft_add_string(new_str, tab[i]);
	}
	return (new_str);
}

void	ft_get_cmd(t_data *data, char *str)
{
	int		i;
	char	*new_str;
	char	**tab;

	if (str)
	{
		new_str = NULL;
		tab = ft_split_mn(str, ' ');
		i = 0;
		while (tab[i])
		{
			if (i > 0)
				new_str = ft_create_arg(tab, new_str, i);
			i++;
		}
		data->cmd = ft_copy_str(tab[0]);
		data->cmd = ft_cmd_with_path(data->cmd);
		data->arg = new_str;
		ft_free_tab(tab);
	}
}
