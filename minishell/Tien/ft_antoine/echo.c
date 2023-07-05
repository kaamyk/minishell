/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/20 16:15:36 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*get_var_name(char *arg)
{
	char	*var;
	size_t	i;

	i = 0;
	while (ft_isalpha(arg[i]) == 1 || arg[i] == '_')
		++i;
	if (i == 0)
	{
		var = ft_calloc(1, 1);
		return (var);
	}
	var = malloc(i + 1);
	if (var == NULL)
		return (free_all(NULL, NULL, NULL));
	var[i--] = 0;
	while (1)
	{
		var[i] = arg[i];
		if (i == 0)
			break ;
		--i;
	}
	return (var);
}

bool	ft_echo(t_data *data)
{
	size_t	i;
	bool	nl;
	char	*arg;

	arg = data->arg;
	i = 0;
	while (arg[i] == ' ')
		++i;
	nl = print_nl(arg + i);
	if (nl == false)
		i += 3;
	while (arg[i] != 0)
	{
		if (arg[i] == '"' || arg[i] == '\'')
			i += print_quotes(arg + i, arg[i]);
		else if (arg[i] == '$' && arg[i + 1] != 0 && arg[i + 1] != ' '
			&& arg[i + 1] != '?' && ft_isalpha(arg[i + 1]) == 1)
			i += print_var(get_var_name(arg + i + 1)) + 1;
		else
		{
			write(1, arg + i, 1);
			++i;
		}
	}
	if (nl == true)
		printf("\n");
	return (0);
}
