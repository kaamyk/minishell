/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/08/24 23:03:03 by antoine          ###   ########.fr       */
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

void	print_content(char *arg)
{
	char	c;
	size_t	i;

	i = 0;
	c = 0;
	while (arg[i] != 0)
	{
		if (c == 0 && (arg[i] == '"' || arg[i] == '\''))
			c = arg[i];
		else if (c != 0 && (arg[i] == c || arg[i] == c))
			c = 0;
		else
			write(STDOUT_FILENO, arg + i, 1);
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

size_t	skip_opt(char *arg)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (arg[i] && arg[i] == '-')
	{
		if (ft_strncmp(arg + i, "-n", 2) != 0)
			break ;
		if (arg[i + 2] == 0 || arg[i + 2] == ' ')
			i += 2 + ((size_t)((arg[i + 2] == ' ') & 1));
		else
		{
			j = 2;
			while (arg[i + j] && arg[i + j] != ' ')
			{
				if (arg[i + j] != 'n')
					return (i);
				++j;
			}
			i += j + ((size_t)((arg[i + j] == ' ') & 1));
		}
	}
	return (i);
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
	i += skip_opt(data->arg + i);
	print_content(data->arg + i);
	if (nl == true)
		printf("\n");
	data->exit_code = 0;
	return (0);
}
