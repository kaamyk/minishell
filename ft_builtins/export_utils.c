/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/09/01 10:24:05 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_export_inputs(t_data *data, char *var)
{
	size_t	j;

	if (var == NULL || ft_strlen(var) == 0)
		return (0);
	if (ft_isalpha(var[0]) == 0 && var[0] != '_')
	{
		data->exit_code = 1;
		return (1);
	}
	j = 1;
	while (var[j] && var[j] != '=')
	{
		if (ft_isalnum(var[j]) == 0 && var[j] != '_' && var[j] != '=')
		{
			data->exit_code = 1;
			return (1);
		}
		++j;
	}
	return (0);
}

char	*get_variable(char *arg, size_t *i)
{
	char	*res;
	char	c;
	size_t	start;
	size_t	end;

	start = *i;
	while (arg[*i] && arg[*i] != ' ')
	{
		if (arg[*i] == '\'' || arg[*i] == '"')
		{
			c = arg[(*i)++];
			while (arg[*i] && arg[*i] != c)
				++(*i);
			if (arg[*i] == c)
				++(*i);
		}
		else
			++(*i);
	}
	end = *i;
	res = ft_substr(arg, start, end - start);
	return (res);
}

char	**split_inputs(char *arg)
{
	char	**res;
	char	*var;
	size_t	i;

	i = 0;
	res = NULL;
	while (arg[i])
	{
		while (arg[i] && (arg[i] == ' ' || arg[i] == '\t'))
			++i;
		var = get_variable(arg, &i);
		if (ft_strchr(arg, '\''))
			var = del_char(var, '\'');
		else if (ft_strchr(var, '"'))
			var = del_char(var, '"');
		res = add_variable(res, var);
		free(var);
	}
	return (res);
}
