/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/21 17:16:12 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var_name(char *arg)
{
	char	*var;
	size_t	i;

	i = 0;
	while (ft_isalpha(arg[i]) != 0 || arg[i] == '_')
		++i;
	if (i == 0)
	{
		var = ft_calloc(1, 1);
		return (var);
	}
	var = malloc(i + 1);
	if (var == NULL)
		return (NULL);
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

size_t	print_quotes(char **env, char *arg, char c)
{
	size_t	i;

	i = 1;
	while (arg[i] && arg[i] != c)
	{
		if (arg[i] == '$' && arg[i + 1] != 0 && arg[i + 1] != ' '
			&& arg[i + 1] != '?' && ft_isalpha(arg[i + 1]) == 1)
			i += print_var(env, get_var_name(arg + i + 1)) + 1;
		else
			printf("%c", arg[i]);
		++i;
	}
	return (i);
}

void	print_content(char *arg, int exit_code, char **env)
{
	size_t	i;

	i = 0;
	while (arg[i] != 0)
	{
		if (arg[i] == '"' || arg[i] == '\'')
			i += print_quotes(env, arg + i, arg[i]);
		else if (arg[i] == '$' && arg[i + 1] != 0 && arg[i + 1] != ' ')
		{
			if (arg[i + 1] == '?')
			{
				printf("%d", exit_code);
				i += 2;
			}
			else
				i += print_var(env, get_var_name(arg + i + 1)) + 1;
		}
		else
		{
			printf("%c", arg[i]);
			++i;
		}
	}
}

bool	ft_echo(t_data *data)
{
	bool	nl;
	size_t	i;

	i = 0;
	if (data->arg == NULL || ft_strlen(data->arg) == 0)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (data->arg[i] == ' ')
		++i;
	nl = !(data->arg[0] == '-' && ft_strnstr(data->arg, "-n ", 3) != NULL);
	if (nl == false)
		i += 3;
	print_content(data->arg + i, data->exit_code, data->env);
	if (nl == true)
		printf("\n");
	return (0);
}
