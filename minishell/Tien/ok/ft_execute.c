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

bool	ft_pwd(void)
{
	char	cwd[10000];

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

void	ft_builtins(t_data *data, char **cmd)
{
	data->exit_code = 0;
	if (ft_compare_str(data->cmd, "pwd") == true)
	{
		ft_pwd();
	}
	else if (ft_compare_str(data->cmd, "export") == true)
	{
		ft_export(data);
	}
	else if (ft_compare_str(data->cmd, "unset") == true)
	{
		ft_unset(data);
	}
	else if (ft_compare_str(data->cmd, "env") == true)
	{
		ft_env(data);
	}
	else if (ft_compare_str(data->cmd, "echo") == true)
	{
		ft_echo(data);
	}
	else if (ft_compare_str(data->cmd, "cd") == true)
	{
		ft_cd(data);
	}
	else
	{
		ft_other_cmd(data, cmd);
	}
}
