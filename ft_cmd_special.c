/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:44:08 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/28 16:44:19 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
<< limiter export salut > file
La commande change le valuer de la variable env
*/
int	ft_run_cmd_special(t_data *data)
{
	int		id;

	id = 0;
	if (ft_compare_str(data->cmd, "cd") == true)
		id = 3;
	else if (ft_compare_str(data->cmd, "exit") == true)
		id = 4;
	else if (ft_compare_str(data->cmd, "export") == true && data->arg)
		id = 6;
	else if (ft_compare_str(data->cmd, "unset") == true && data->arg)
		id = 7;
	return (id);
}

void	ft_cmd_special(t_data *data)
{
	int		i;
	int		id;
	char	**tab;

	tab = data->tab_cmd;
	i = 0;
	while (tab[i])
	{
		if (tab[i][0] != '>' && tab[i][0] != '<')
		{
			ft_get_cmd(data, tab[i]);
			id = ft_run_cmd_special(data);
			if (id != 0)
				ft_builtins(data, id);
			free(data->cmd);
			if (data->arg)
				free(data->arg);
		}
		i++;
	}
}
