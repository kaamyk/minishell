/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:27:01 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/23 12:57:30 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env;

char	*ft_other_cmd2(char *cmd, bool check)
{
	DIR				*dp;
	struct dirent	*dirp;
	char			*dir;

	dp = opendir("/usr/bin");
	dirp = readdir(dp);
	while (dirp != NULL)
	{
		if (ft_compare_str(cmd, dirp->d_name) == true)
		{
			dir = ft_strjoin("/usr/bin/", cmd);
			check = true;
		}
		dirp = readdir(dp);
	}
	if (closedir(dp) == -1)
		perror("closedir");
	if (check == true)
		return (dir);
	return (0);
}

bool	ft_other_cmd(t_data *data)
{
	char	**argvec;

	argvec = (char **)malloc(3 * sizeof(char *));
	if (!argvec)
		return (1);
	argvec[0] = data->cmd;
	argvec[1] = data->arg;
	argvec[2] = NULL;
	if (execve(data->cmd, argvec, NULL) == -1)
	{
		ft_error(NOT_FOUND, data->cmd, 0);
		free_tab_mn(argvec);
		return (1);
	}
	free_tab_mn(argvec);
	return (0);
}

char	*read_print2(t_data *data)
{
	int		fd[2];

	data->run = true;
	pipe(fd);
	if (fork() == 0)
	{
		close(fd[0]);
		if (data->print == false)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		ft_other_cmd(data);
		ft_free_all(data);
		exit (0);
	}
	else
		return (join_print(fd));
}
