/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:52:17 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/20 18:29:39 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**********************************/
/* Set redirects [>] [<] [>>] [<<]*/
/**********************************/

//extern t_env	*g_env;

void	here_doc2(char *limiter, int *fd, bool s_double)
{
	char	*line;

	if (s_double == true)
		line = ft_redirection3(limiter);
	else
		line = ft_redirection2(limiter);
	if (line)
	{
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
}

void	here_doc(t_data *data, char *limiter, bool s_double)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		here_doc2(limiter, fd, s_double);
		if (data->s_bonus)
		{
			free(data->tab_logic);
			ft_free_tab(data->tab_cmd_logic);
		}
		free(limiter);
		ft_free_tab(data->tab_cmd);
		//free_env(g_env);
		exit(EXIT_SUCCESS);
	}
	else
	{
		free(limiter);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, &data->exit_code, 0);
	}
}

void	ft_write(t_data *data, char	*file, bool s_double)
{
	pid_t	pid;
	int		fd;

	pid = fork();
	if (pid == 0)
	{
		if (s_double == true)
			fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
		else
			fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		dup2(fd, STDOUT_FILENO);
		execute(data);
		if (data->s_bonus)
		{
			free(data->tab_logic);
			ft_free_tab(data->tab_cmd_logic);
		}
		free(file);
		ft_free_tab(data->tab_cmd);
		//free_env(g_env);
		exit(data->exit_code);
	}
	waitpid(pid, &data->exit_code, 0);
	ft_exit_code(data);
}

bool	ft_redirection_output(t_data *data, char *str)
{
	pid_t	pid;
	char	*limiter;

	if (str[0] == '<')
	{
		pid = fork();
		if (pid == 0)
		{
			data->file = str;
			limiter = ft_find_str(data->file);
			if (str[1] == '<')
				here_doc(data, limiter, true);
			else
				here_doc(data, limiter, false);
			if (data->s_bonus)
			{
				free(data->tab_logic);
				ft_free_tab(data->tab_cmd_logic);
			}
			ft_free_tab(data->tab_cmd);
			//free_env(g_env);
			exit(data->exit_code);
		}
		waitpid(pid, &data->exit_code, 0);
		ft_exit_code(data);
		return (1);
	}
	return (0);
}

bool	ft_redirection_input(t_data *data, int i)
{
	char	*file;

	if (data->tab_cmd[i][0] == '>')
	{
		data->file = data->tab_cmd[i];
		if (i > 0 && data->tab_cmd[i - 1][0] == '>')
			data->str = NULL;
		file = ft_find_str(data->file);
		if (data->tab_cmd[i][1] == '>')
			ft_write(data, file, true);
		else
			ft_write(data, file, false);
		free(file);
		return (1);
	}
	return (0);
}
