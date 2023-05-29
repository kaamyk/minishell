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

void	ft_pwd()
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

// int		ft_redirections(char *command)
// {
// 	if (command[0] == '<')
// 	{
// 		printf("%s\n", command);
// 		return (1);
// 	}
// 	else if (command[0] == '>')
// 	{
// 		printf("%s\n", command);
// 		return (1);
// 	}
// 	return (0);
// }

int	ft_dollar_symbol(char *command)
{
	char	*var;
	char	*value;

	var = ft_strchr(command, '$');
	if (var != 0)
	{
		value = getenv(&var[1]);
		printf("%s\n", value);
		return (1);
	}
	return (0);
}

int	ft_builtins(char *command, char *arg)
{
	if (ft_strnstr(command, "exit", 4) != 0)
	{
		printf("%s\n", command);
		exit(0);
	}
	else if (ft_strnstr(command, "pwd", 3) != 0)
	{
		ft_pwd();
		return (1);
	}
	else if (ft_strnstr(command, "export", 6) != 0)
	{
		printf("%s\n", command);
		return (1);
	}
	else if (ft_strnstr(command, "unset", 5) != 0)
	{
		printf("%s\n", command);
		return (1);
	}
	else if (ft_strnstr(command, "env", 3) != 0)
	{
		printf("%s\n", command);
		return (1);
	}
	else if (ft_strnstr(command, "echo", 4) != 0)
	{
		printf("%s\n", command);
		ft_echo(arg);
		return (1);
	}
	return (0);
}

void	ft_determine_command(char *command, char *arg)
{
	//printf("--> %s %ld\n", command, ft_strlen(command));
	if (ft_builtins(command, arg) == 0
		&& ft_dollar_symbol(command) == 0
		&& ft_other_command(command) == 0)
	{
		ft_error(NOT_FOUND, command, NULL);
	}
	//ft_strlen(command) == 1 && 
}
