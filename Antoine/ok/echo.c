/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/16 09:56:18 by antoine          ###   ########.fr       */
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

bool	print_nl(char *arg)
{
	if (arg[0] == '-' && ft_strnstr(arg, "-n ", 3) != NULL)
		return (false);
	return (true);
}

bool	ft_echo(char *arg)
{
	size_t	i;
	bool	nl;

	i = 0;
	while (arg[i] == ' ')
		++i;
	nl = print_nl(arg + i);
	if (nl == false)
		i += 3;
	while (arg[i])
	{
		if (arg[i] == '"' || arg[i] == '\'')
			i += print_quotes(arg + i, arg[i]);
		else if (arg[i] == '$')
			i += print_var(arg + i + 1);
		else
		{
			write(STDOUT_FILENO, &arg[i], 1);
			++i;
		}
	}
	if (nl == true)
		write (STDOUT_FILENO, "\n", 1);
	return (0);
}
