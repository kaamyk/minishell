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

void	ft_exit_code(t_data *data)
{
	if (data->exit_code == 256)
		data->exit_code = 1;
	else if (data->exit_code == 512)
		data->exit_code = 2;
	else if (data->exit_code == 32512)
		data->exit_code = 127;
}

void	ft_execute_without_pipe(t_data *data)
{
	int		i;

	if (data->nb_cmd > 1)
		data->print = false;
	data->file = NULL;
	data->str = NULL;
	i = 0;
	while (data->tab_cmd[i])
	{
		if (data->tab_cmd[i + 1] == 0)
			data->print = true;
		if (ft_redirection_output(data, data->tab_cmd[i]) == false
			&& ft_redirection_input(data, i) == false)
		{
			if (data->tab_cmd[i][0] == '|')
				data->str = &data->tab_cmd[i][2];
			else
				data->str = data->tab_cmd[i];
			if ((data->tab_cmd[i + 1] != 0 && data->tab_cmd[i + 1][0] != '>')
				|| data->tab_cmd[i + 1] == 0)
				ft_pipex(data);
		}
		i++;
	}
}

void	ft_execute_with_pipe(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_execute_without_pipe(data);
		if (data->s_bonus)
		{
			free(data->tab_logic);
			ft_free_tab(data->tab_cmd_logic);
		}
		ft_free_tab(data->tab_cmd);
		free_env(g_env);
		exit(data->exit_code);
	}
	waitpid(pid, &data->exit_code, 0);
	ft_exit_code(data);
}

/*
Send the commands
*/
void	ft_execute_cmd(t_data *data)
{
	if (data->s_pipe == true)
		ft_execute_with_pipe(data);
	else
		ft_execute_without_pipe(data);
	ft_free_tab(data->tab_cmd);
}
