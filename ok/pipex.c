/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 10:33:51 by gcollet           #+#    #+#             */
/*   Updated: 2021/08/13 18:13:03 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env;

void	execute(t_data *data)
{
	ft_get_cmd(data, data->str);
	ft_builtins(data);
	if (data->str)
	{
		free(data->cmd);
		free(data->arg);
	}
}

void	child_process(t_data *data)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(data);
		if (data->s_bonus)
		{
			free(data->tab_logic);
			ft_free_tab(data->tab_cmd_logic);
		}
		ft_free_tab(data->tab_cmd);
		free_env(g_env);
		exit(data->exit_code);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, &data->exit_code, 0);
		ft_exit_code(data);
	}
}

void	ft_pipex(t_data *data)
{
	if (data->print == 0 && data->s_pipe == true)
		child_process(data);
	else
	{
		execute(data);
	}
}
