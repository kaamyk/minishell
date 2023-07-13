/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:52:17 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/17 15:52:52 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**********************************/
/* Set redirects [>] [<] [>>] [<<]*/
/**********************************/

extern t_env	*g_env;

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
		free(limiter);
		ft_free_tab(data->tab_cmd);
		free_env(g_env);
		exit(EXIT_SUCCESS);
	}
	else
	{
		free(limiter);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
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
		free(file);
		dup2(fd, STDOUT_FILENO);
		execute(data);
	}
	waitpid(pid, &data->exit_code, 0);
	ft_exit_code(data);
}
