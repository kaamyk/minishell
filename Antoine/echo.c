/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/07 18:34:33 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env;

size_t	print_quotes(char *arg, char c)
{
	size_t	i;

	i = 1;
	while (arg[i] && arg[i] != c)
	{
		write(STDOUT_FILENO, &arg[i], 1);
		++i;
	}
	return (i);
}

void	ft_echo(char *command, char *arg)
{
	size_t	i;

	(void)command;
	i = 0;
	while (arg[i] == ' ')
		++i;
	while (arg[i])
	{
		if (arg[i] == '"' || arg[i] == '\'')
			i += print_quotes(arg + i, arg[i]);
		else if (arg[i] == '$')
			i += print_var(arg + i);
		else
			write(STDOUT_FILENO, &arg[i], 1);
		++i;
	}
	write (STDOUT_FILENO, "\n", 1);
}
