/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 10:26:01 by gcollet           #+#    #+#             */
/*   Updated: 2022/02/06 13:58:34 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_code(t_data *data)
{
	if (data->exit_code == 256)
		data->exit_code = 1;
	else if (data->exit_code == 512)
		data->exit_code = 2;
	else if (data->exit_code == 32512)
		data->exit_code = 127;
}

void	ft_create_cmd(t_data *data, char **tab)
{
	int	i;

	i = 1;
	data->cmd = tab[0];
	data->arg = NULL;
	while (tab[i])
	{
		if (i == 1)
			data->arg = ft_copy_str(tab[i]);
		else
			data->arg = ft_add_string(data->arg, tab[i]);
		i++;
	}
}

void	execute(t_data *data)
{
	int		i;
	char	**cmd;

	cmd = ft_split(data->str, ' ');
	ft_create_cmd(data, cmd);
	ft_builtins(data, cmd);
	i = -1;
	while (cmd[++i])
		free(cmd[i]);
	if (data->arg)
		free(data->arg);
	free(cmd);
}
