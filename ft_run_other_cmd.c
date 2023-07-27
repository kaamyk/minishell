/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_other_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:05:42 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/24 13:06:40 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***********************************/
/*   Execute the other commands    */
/* [ls] [grep] [cat] [wc -c] [...] */
/***********************************/

void	ft_exit_code(t_data *data)
{
	if (data->exit_code == 256)
		data->exit_code = 1;
	else if (data->exit_code == 512)
		data->exit_code = 2;
	else if (data->exit_code == 32512)
		data->exit_code = 127;
}

char	*find_path2(char *cmd, char **paths)
{
	char	*part_path;
	char	*path;
	int		i;

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

char	*find_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (envp[i] == NULL)
		return (0);
	paths = ft_split(envp[i] + 5, ':');
	return (find_path2(cmd, paths));
}

void	ft_other_cmd_with_pipe(t_data *data)
{
	char	**cmd;
	char	*path;

	cmd = ft_split_mn(data->str, ' ');
	ft_delete_quotes(cmd);
	cmd[0] = ft_cmd_with_path(cmd[0]);
	path = find_path(cmd[0], data->env);
	if (path)
	{
		if (execve(path, cmd, data->env) == -1)
			data->exit_code = 127;
	}
	else
		data->exit_code = 127;
	free(path);
	ft_free_tab(cmd);
}

void	ft_other_cmd_without_pipe(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_other_cmd_with_pipe(data);
		ft_free_end(data);
		exit(data->exit_code);
	}
	waitpid(pid, &data->exit_code, 0);
	ft_exit_code(data);
}
