/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:03:30 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/17 16:03:32 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*********************/
/* Execute the logic */
/*      || OR        */
/*      && AND       */
/*********************/

void	ft_run_bonus2(t_data *data, char *str)
{
	char	*new_str;

	new_str = ft_create_str_without_quotes(data, str);
	new_str = ft_parsing_mandatory_part2(data, new_str);
	data->tab_cmd = ft_create_tab_cmd(data, new_str);
	ft_run_cmd(data);
}

void	ft_run_bonus(t_data *data)
{
	int		i;
	char	**tab;

	tab = data->tab_cmd_logic;
	i = 0;
	while (tab[i])
	{
		tab[i] = ft_delete_space(tab[i]);
		if (i == 0)
			ft_run_bonus2(data, tab[i]);
		else
		{
			if (i <= data->nb_logic)
			{
				if (data->exit_code == 0 && data->tab_logic[i - 1] == 0)
					ft_run_bonus2(data, tab[i]);
				else if (data->exit_code != 0 && data->tab_logic[i - 1] == 1)
					ft_run_bonus2(data, tab[i]);
			}
		}
		i++;
	}
	ft_free_tab(tab);
	free(data->tab_logic);
}
