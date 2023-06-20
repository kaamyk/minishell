/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/26 11:23:28 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env;

void	ft_free_all(t_data *data)
{
	free(data->cmd);
	free(data->arg);
	free_tab_mn(data->tab_cmd);
	free_env(g_env);
}

bool	ft_pwd(char *arg)
{
	char	cwd[10000];

	(void)arg;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
	}
	else
	{
		perror("ft_pwd() error");
		return (1);
	}
	return (0);
}

bool	ft_dollar_symbol(char *command)
{
	char	*var;
	char	*value;

	var = ft_strchr(command, '$');
	if (var != 0)
	{
		value = getenv(&var[1]);
		printf("%s\n", value);
		return (true);
	}
	return (false);
}

void	ft_builtins(t_data *data)
{
	char	*tmp;

	if (data->result)
		free(data->result);
	data->result = NULL;
	if (ft_compare_str(data->cmd, "exit") == true)
	{
		ft_free_all(data);
		exit(0);
	}
	else if (ft_compare_str(data->cmd, "pwd") == true)
	{
		data->result = read_print(data, ft_pwd);
	}
	else if (ft_compare_str(data->cmd, "export") == true)
	{
		data->result = read_print(data, ft_export);
	}
	else if (ft_compare_str(data->cmd, "unset") == true)
	{
		ft_unset(data->arg);
		print_env(0);
	}
	else if (ft_compare_str(data->cmd, "env") == true)
	{
		data->result = read_print(data, ft_env);
	}
	else if (ft_compare_str(data->cmd, "echo") == true)
	{
		data->result = read_print(data, ft_echo);
	}
	else if (ft_compare_str(data->cmd, "cd") == true)
	{
		data->result = read_print(data, ft_cd);
	}
	else
	{
		tmp = data->cmd;
		data->cmd = ft_other_cmd2(data->cmd, false);
		if (data->cmd)
		{
			free(tmp);
			data->result = read_print2(data);
		}
	}
	if (data->run == false)
		ft_error(NOT_FOUND, data->cmd, 0);
}

void	ft_determine_command(t_data *data)
{
	// printf("[%s %ld]\n", data->cmd, ft_strlen(data->cmd));
	// printf("[%s %ld]\n", data->arg, ft_strlen(data->arg));
	ft_builtins(data);
}
