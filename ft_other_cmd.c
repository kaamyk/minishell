/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:27:01 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/20 18:42:55 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// extern t_env	*g_env;

char	*ft_get_path(char *cmd)
{
	DIR				*dp;
	struct dirent	*dirp;
	char			*dir;

	dir = NULL;
	dp = opendir("/usr/bin");
	dirp = readdir(dp);
	while (dirp != NULL)
	{
		if (ft_compare_str(cmd, dirp->d_name) == true)
			dir = ft_strjoin("/usr/bin/", cmd);
		dirp = readdir(dp);
	}
	if (closedir(dp) == -1)
		perror("closedir");
	return (dir);
}

void	ft_execute_other_cmd(t_data *data)
{
	char	**argvec;

	argvec = ft_split_mn(data->str, ' ');
	if (execve(data->cmd, argvec, NULL) == -1)
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
	}
	waitpid(pid, &data->exit_code, 0);
	ft_exit_code(data);
}

void	ft_other_cmd(t_data *data)
{
	char	*tmp;

	tmp = data->cmd;
	data->cmd = ft_get_path(data->cmd);
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
