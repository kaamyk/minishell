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

/********************************/
/* Execute pwd | grep h | wc -c */
/********************************/

void	ft_exit_code(t_data *data)
{
	if (data->exit_code == 256)
		data->exit_code = 1;
	else if (data->exit_code == 512)
		data->exit_code = 2;
	else if (data->exit_code == 32512)
		data->exit_code = 127;
}

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

void	ft_put_value_in_pipe(t_data *data)
{
	if (data->s_heredoc == true && data->output)
	{
		printf("%s\n", data->output);
		free(data->output);
	}
	else if (data->s_heredoc == false)
		execute(data);
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
		ft_put_value_in_pipe(data);
		ft_free_end(data);
		exit(data->exit_code);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, &data->exit_code, WNOHANG);
		ft_exit_code(data);
	}
}

void	ft_pipex(t_data *data)
{
	if (data->s_heredoc == true)
	{
		child_process(data);
		data->s_heredoc = false;
	}
	if (data->print == 0 && data->s_pipe == true)
		child_process(data);
	else
		execute(data);
}
