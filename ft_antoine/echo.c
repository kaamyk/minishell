/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/08/22 17:49:50 by anvincen         ###   ########.fr       */
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

void	print_content(char *arg, int exit_code, char **env)
{
	size_t	i;

	(void) exit_code;
	(void) env;
	i = 0;
	while (arg[i] != 0)
	{
		printf("%c", arg[i]);
		++i;
	}
}

bool	opt_nl(char *arg)
{
	size_t	i;

	if (arg[0] != '-')
		return (true);
	else
	{
		i = 1;
		while (arg[i] && arg[i] != ' ')
		{
			if (arg[i] != 'n')
				return (true);
			++i;
		}
	}
	return (false);
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
	nl = opt_nl(data->arg);
	if (nl == false)
		i += 2;
	while (data->arg[i] || data->arg[i] == 'n' || data->arg[i] == ' ' || data->arg[i] == '\t')
		++i;
	printf("data->arg + i == [%s]\n", data->arg + i);
	while (data->arg + i && ft_strncmp(data->arg + i, "-n", 2) == 0)
		i += 2;
	print_content(data->arg + i, data->exit_code, data->env);
	if (nl == true)
		printf("\n");
	data->exit_code = 0;
	return (0);
}
