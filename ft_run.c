/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:39:16 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/24 12:44:14 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***************************************************/
/*              Execute the builtins               */
/* [echo] [pwd] [cd] [exit] [env] [export] [unset] */
/***************************************************/

void	ft_run(t_data *data, int i)
{
	char	*tmp;

	if (data->tab_cmd[i][0] == '|')
	{
		if (ft_strlen(data->tab_cmd[i]) == 1)
			return ;
		tmp = data->tab_cmd[i];
		data->tab_cmd[i] = ft_copy_str(&data->tab_cmd[i][2]);
		free(tmp);
	}
	data->tab_cmd[i] = ft_wildcards(data, data->tab_cmd[i]);
	ft_get_cmd(data, data->tab_cmd[i]);
	if (ft_check_builtins(data) == 0)
	{
		data->str = data->tab_cmd[i];
		if (data->s_pipe == true)
			ft_other_cmd_with_pipe(data);
		else
			ft_other_cmd_without_pipe(data);
	}
}

void	ft_run_cmd_without_pipe(t_data *data)
{
	int		i;
	char	**tab;

	tab = data->tab_cmd;
	i = 0;
	while (tab[i])
	{
		ft_run(data, i);
		if (data->exit_code == 127)
			ft_error(NOT_FOUND, data->tab_cmd[i], 0);
		i++;
	}
}

/*
<< limiter export salut > file
La commande change le valuer de la variable env
*/
int	ft_cmd_special(t_data *data)
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

void	ft_one_cmd(t_data *data)
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
			id = ft_cmd_special(data);
			if (id != 0)
				ft_builtins(data, id);
			free(data->cmd);
			if (data->arg)
				free(data->arg);
		}
		i++;
	}
}

void	ft_run_cmd(t_data *data)
{
	data->str_with_wildcard = NULL;
	data->s_infile = ft_check_infile(data);
	data->s_outfile = ft_check_outfile(data);
	if (data->s_pipe == true
		|| data->s_infile == true
		|| data->s_outfile == true)
		ft_run_cmd_with_pipe(data);
	else
		ft_run_cmd_without_pipe(data);
	if (data->s_pipe == false
		&& (data->s_infile == true || data->s_outfile == true))
		ft_one_cmd(data);
	ft_free_tab(data->tab_cmd);
}
