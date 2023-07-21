/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/18 16:51:44 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	handle_inputs(char **env, char **inputs, bool *exit)
{
	char	**key;
	char	**value;
	size_t	i;

	key = init_keys(env, len_list(env));
	value = init_values(env);
	i = 0;
	while (inputs[i])
	{
		if (check_double(inputs[i], key, value) == 0)
		{
			if (find_var_rank(input[i], key, value) != -1
				&& replace_value(env, value[i], find_var_rank(env, key[i]) != 0))
				return (1);
			else if (add_variable(key[i], value[i], env, env[i]) != 0)
				return (1);
		}
		else
			*exit = 1;
		++i;
	}
}

bool	ft_export(t_data *data)
{
	char	**inputs;
	bool	exit;

	exit = 0;
	if (data->arg == NULL || ft_strlen(data->arg) == 0)
		return (print_env(data->s_env, 1));
	inputs = init_env(ft_split(data->arg, ' '));
	if (inputs == NULL)
		return (1);
	if (handle_inputs(data->env, inputs, &exit) != 0)
		return (1);
	// free_env(res);
	return (exit);
}