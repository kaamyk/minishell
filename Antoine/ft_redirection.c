/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:52:17 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/21 09:23:34 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env;

void	ft_free_redirection(t_data *data, char *arg1, char *arg2)
{
	free(arg1);
	free(arg2);
	if (data->double_input == true)
		free(data->result);
	free_tab_mn(data->tab_cmd);
	free_env(g_env);
}

void	ft_input(t_data *data, char *arg1, char *arg2, bool input)
{
	int		newfd;

	newfd = 0;
	if (input == true)
		newfd = open(arg2, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (input == false)
		newfd = open(arg2, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (newfd < 0)
	{
		perror(arg2);
		return ;
	}
	dup2(newfd, 1);
	// if (!arg1)
	// 	printf("");
	if (arg1)
	{
		printf("%s", arg1);
		if (arg1[ft_strlen(arg1) - 1] != '\n')
			printf("\n");
	}
	ft_free_redirection(data, arg1, arg2);
	exit (0);
}

void	ft_redirection(t_data *data, char *arg1, char *arg2, bool input)
{
	int		fd[2];

	pipe(fd);
	if (fork() == 0)
	{
		close(fd[0]);
		ft_input(data, arg1, arg2, input);
	}
	else
	{
		close(fd[1]);
		wait(NULL);
	}
}
