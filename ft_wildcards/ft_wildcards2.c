/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:47:24 by xuluu             #+#    #+#             */
/*   Updated: 2023/09/01 11:18:43 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**************************************/
/* List current files and directories */
/**************************************/

void	ft_lire_current_directory(t_data *data, int *fd)
{
	char	*argv[3];

	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	argv[0] = "/bin/ls";
	argv[1] = ".";
	argv[2] = NULL;
	execve(argv[0], argv, data->env);
	free(data->str_with_wildcard);
	ft_free_tab(data->tab_wildcards);
	ft_free_tab(data->tab_quotes);
	ft_free_end(data);
	exit(data->exit_code);
}

char	*ft_get_current_directory(t_data *data)
{
	int		fd[2];
	pid_t	pid;
	char	*str;

	str = NULL;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		ft_lire_current_directory(data, fd);
	}
	else
	{
		close(fd[1]);
		str = ft_read_pipe(fd[0]);
		waitpid(pid, &data->exit_code, 0);
		data->exit_code = data->exit_code / 256;
	}
	return (str);
}
