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

// int	ft_exit(t_data *data)
// {
// 	ft_free_tab(data->tab_cmd);
// 	free_env(g_env);
// 	exit(data->exit_code);
// }

void	ft_exit_code(t_data *data)
{
	if (data->exit_code == 256)
		data->exit_code = 1;
	else if (data->exit_code == 512)
		data->exit_code = 2;
	else if (data->exit_code == 32512)
		data->exit_code = 127;
}

bool	ft_redirection_output(t_data *data, char *str)
{
	char	*limiter;

	if (str[0] == '<')
	{
		data->file = str;
		limiter = ft_find_str(data->file);
		if (str[1] == '<')
			here_doc(data, limiter, true);
		else
			here_doc(data, limiter, false);
		return (1);
	}
	return (0);
}

bool	ft_redirection_input(t_data *data, char *str)
{
	char	*file;

	if (str[0] == '>')
	{
		data->file = str;
		file = ft_find_str(data->file);
		if (str[1] == '>')
			ft_write(data, file, true);
		else
			ft_write(data, file, false);
		free(file);
		return (1);
	}
	return (0);
}

void	ft_execute_with_pipe2(t_data *data)
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
			&& ft_redirection_input(data, data->tab_cmd[i]) == false)
		{
			if (data->tab_cmd[i][0] == '|')
				data->str = &data->tab_cmd[i][2];
			else
				data->str = data->tab_cmd[i];
			ft_pipex(data);
		}
		i++;
	}
	ft_free_tab(data->tab_cmd);
}

void	ft_execute_with_pipe(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_execute_with_pipe2(data);
		free_env(g_env);
		exit(data->exit_code);
	}
	waitpid(pid, &data->exit_code, 0);
	ft_exit_code(data);
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
			&& ft_redirection_input(data, data->tab_cmd[i]) == false)
		{
			data->str = data->tab_cmd[i];
			execute(data);
		}
		i++;
	}
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
