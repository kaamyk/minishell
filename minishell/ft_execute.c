/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/26 11:23:28 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	cwd[10000];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
	}
	else
	{
		perror("ft_pwd() error");
		return ;
	}
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

bool	ft_builtins(t_data *data)
{
	char	*str;

	str = NULL;
	if (ft_strncmp(data->cmd, "exit", ft_strlen(data->cmd)) == 0)
	{
		printf("%s\n", data->cmd);
		exit(0);
	}
	else if (ft_strncmp(data->cmd, "pwd", ft_strlen(data->cmd)) == 0)
	{
		ft_pwd();
		return (true);
	}
	else if (ft_strncmp(data->cmd, "export", ft_strlen(data->cmd)) == 0)
	{
		ft_export(data->arg);
		return (true);
	}
	else if (ft_strncmp(data->cmd, "unset", ft_strlen(data->cmd)) == 0)
	{
		//printf("%s\n", data->cmd);
		ft_unset(data->arg);
		print_env(0);
		return (true);
	}
	else if (ft_strncmp(data->cmd, "env", ft_strlen(data->cmd)) == 0)
	{
		ft_env();
		return (true);
	}
	else if (ft_strncmp(data->cmd, "echo", ft_strlen(data->cmd)) == 0)
	{
		str = read_print(ft_echo, data->arg, data->print);
		//return (true);
	}
	printf("[%s]\n", str);
	free(str);
	return (false);
}

bool	ft_one_arg(char c)
{
	if (c == '\n'
		|| c == ' '
		|| c == '	'
		|| c == ':'
		|| c == '!')
		return (true);
	else if (c == '$')
	{
		printf("%c\n", c);
		return (true);
	}
	return (false);
}

void	ft_determine_command(t_data *data)
{
	// printf("[%s %ld]\n", data->cmd, ft_strlen(data->cmd));
	// printf("[%s %ld]\n", data->arg, ft_strlen(data->arg));
	ft_builtins(data);
}
