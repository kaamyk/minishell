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

void	ft_delete_q(t_data *data, char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		tab[i] = ft_delete_quotes(data, tab[i]);
		i++;
	}
}

void	ft_other_cmd_with_pipe(t_data *data)
{
	char	**cmd;
	char	*path;

	cmd = ft_split_mn(data->str, ' ');
	ft_delete_q(data, cmd);
	path = NULL;
	if (ft_strnstr(cmd[0], PATH, 5) != 0)
		path = ft_copy_str(cmd[0]);
	else if (ft_strrchr(cmd[0], '/') == 0)
		path = find_path(cmd[0], data->env);
	if (path)
	{
		if (execve(path, cmd, data->env) == -1)
			data->exit_code = 127;
		else
			data->exit_code = 0;
	}
	else
		data->exit_code = 127;
	if (path)
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
