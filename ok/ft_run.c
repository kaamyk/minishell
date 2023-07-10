/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:51:33 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/23 17:52:23 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env;

void	ft_free_tab(char **tab, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_print_tab(char **tab, int len)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < len)
	{
		if (tab[i][0] == '|')
		{
			tmp = tab[i];
			tab[i] = ft_find_str(tab[i], '|');
			free(tmp);
			tab[i] = ft_delete_space(tab[i]);
		}
		printf("[%s]", tab[i]);
		i++;
	}
	printf("\n");
}

/*
Send the commands
*/
void	ft_execute_cmd(t_data *data)
{
	ft_print_tab(data->tab_cmd, data->nb_cmd);
	pipex(data);
	ft_free_tab(data->tab_cmd, data->nb_cmd);
}
