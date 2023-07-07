/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 10:33:51 by gcollet           #+#    #+#             */
/*   Updated: 2023/07/07 11:26:05 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env;

void	child_process(t_data *data)
{
	pid_t	pid;
	int		fd[2];

	(void)data;
	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(data);
		free_env(g_env);
		ft_free_tab(data->tab_cmd, data->nb_cmd);
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

void	pipex2(t_data *data, int *fd)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd - 1)
	{
		data->str = data->tab_cmd[i];
		child_process(data);
		i++;
	}
	dup2(fd[1], STDOUT_FILENO);
	data->str = data->tab_cmd[data->nb_cmd - 1];
	if (i == 0 && ft_compare_str(data->str, "exit") == true)
	{
		printf("exit");
	}
	else
		execute(data);
}

int	pipex(t_data *data)
{
	int		fd[2];
	pid_t	pid;
	char	*str;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		pipex2(data, fd);
		close(fd[1]);
		free_env(g_env);
		ft_free_tab(data->tab_cmd, data->nb_cmd);
		exit(data->exit_code);
	}
	else
	{
		str = ft_get_output(fd);
		printf("[%s]\n", str);
		if (str && ft_compare_str(str, "exit") == true)
		{
			free(str);
			ft_free_tab(data->tab_cmd, data->nb_cmd);
			free_env(g_env);
			exit(data->exit_code);
		}
		free(str);
		waitpid(pid, &data->exit_code, 0);
		ft_exit_code(data);
	}
	return (0);
}
