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

extern t_env	*g_env;

void	ft_free_redirection(t_data *data, char *arg2)
{
	free(arg2);
	if (data->nb_cmd > 1)
		ft_free_tab(data->output, data->id_cmd);
	ft_free_tab(data->tab_cmd, data->nb_cmd);
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
		data->exit_code = 1;
	}
	else
	{
		dup2(newfd, 1);
		if (!arg1)
			printf(" ");
		else
		{
			printf("%s", arg1);
			if (arg1[ft_strlen(arg1) - 1] != '\n')
				printf("\n");
		}
	}
	ft_free_redirection(data, arg2);
	exit(data->exit_code);
}

void	ft_redirection(t_data *data, char *arg1, char *arg2, bool input)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_input(data, arg1, arg2, input);
	}
	else
	{
		waitpid(pid, &data->exit_code, 0);
		ft_exit_code(data);
	}
}
