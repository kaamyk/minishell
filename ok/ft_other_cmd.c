/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:27:01 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/17 10:27:51 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***********************************/
/*   Execute the other commands    */
/* [ls] [grep] [cat] [wc -c] [...] */
/***********************************/

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (envp[i] == NULL)
		return (0);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
		{
			ft_free_tab(paths);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free_tab(paths);
	return (0);
}

void	ft_execute_other_cmd(t_data *data)
{
	char	**argvec;

	argvec = ft_split_mn(data->str, ' ');
	if (execve(data->cmd, argvec, data->env) == -1)
	{
		if (data->print == true)
			ft_error(NOT_FOUND, data->cmd, 0);
		data->exit_code = 127;
	}
	ft_free_tab(argvec);
}

void	ft_other_cmd2(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_execute_other_cmd(data);
		if (data->s_bonus)
		{
			free(data->tab_logic);
			ft_free_tab(data->tab_cmd_logic);
		}
		exit(data->exit_code);
	}
	waitpid(pid, &data->exit_code, 0);
	ft_exit_code(data);
}

void	ft_other_cmd(t_data *data)
{
	char	*tmp;

	tmp = data->cmd;
	data->cmd = find_path(data->cmd, data->env);
	if (data->cmd)
	{
		ft_other_cmd2(data);
	}
	else
	{
		data->exit_code = 127;
		if (data->print == true)
			ft_error(NOT_FOUND, tmp, 0);
	}
	free(tmp);
}
