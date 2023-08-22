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

bool	ft_check_pipe(t_data *data, int i)
{
	char	*tmp;

	if (data->tab_cmd[i][0] == '|')
	{
		ft_sleep(21474836);
		data->tab_cmd[i] = ft_delete_space(data->tab_cmd[i]);
		if (ft_strlen(data->tab_cmd[i]) == 1)
		{
			data->exit_code = 0;
			return (1);
		}
		tmp = data->tab_cmd[i];
		data->tab_cmd[i] = ft_copy_str(&data->tab_cmd[i][2]);
		free(tmp);
	}
	return (0);
}

void	ft_run(t_data *data, int i)
{
	if (ft_check_pipe(data, i) == 1 || !data->tab_cmd[i])
		return ;
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
		if (data->exit_code != 0)
			ft_check_exit_code(data, i);
		i++;
	}
}

void	ft_check_infile_outfile_dollar(t_data *data)
{
	int		i;

	data->s_infile = false;
	data->s_outfile = false;
	i = 0;
	while (data->tab_cmd[i])
	{
		data->tab_cmd[i] = del_unused_dollar(data->tab_cmd[i]);
		ft_signe_dollar(data, i);
		if (data->tab_cmd[i] && data->tab_cmd[i][0] == '<')
		{
			data->s_infile = true;
			data->tab_cmd[i] = ft_delete_quotes(data, data->tab_cmd[i]);
			if (data->tab_cmd[i][1] == '<')
				ft_redirection_output(data, i);
		}
		else if (data->tab_cmd[i] && data->tab_cmd[i][0] == '>')
		{
			data->s_outfile = true;
			data->tab_cmd[i] = ft_delete_quotes(data, data->tab_cmd[i]);
		}
		i++;
	}
}

void	ft_run_cmd(t_data *data)
{
	data->str_with_wildcard = NULL;
	ft_check_infile_outfile_dollar(data);
	if (data->s_pipe == true
		|| data->s_infile == true
		|| data->s_outfile == true)
		ft_run_cmd_with_pipe(data);
	else
		ft_run_cmd_without_pipe(data);
	if (data->s_pipe == false
		&& (data->s_infile == true || data->s_outfile == true))
		ft_cmd_special(data);
	ft_free_tab_with_len(data->tab_cmd, data->nb_cmd);
}
