/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/08/25 12:40:30 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	input_valid(char **env, char *inpt_var)
{
	char	*ptr;

	ptr = get_var(env, inpt_var, 0);
	if (ptr == NULL)
		return (0);
	return (1);
}

char	**pop_unvalid_input(char **inputs, char *to_pop, size_t *l, bool *exit)
{
	char	**res;
	size_t	i;
	bool	j;

	res = malloc(sizeof(char *) * (len_list(inputs) + 1));
	if (res == NULL)
		return (inputs);
	*exit = 1;
	i = 0;
	j = 0;
	while (inputs[i])
	{
		if (inputs[i] != to_pop)
			res[i - j] = ft_strdup(inputs[i]);
		else
			j = !j;
		++i;
	}
	res[i - j] = NULL;
	free_list(inputs);
	--(*l);
	return (res);
}

char	**check_inputs(char **env, char **inputs, size_t *len, bool *exit)
{
	char	*i_key;
	size_t	i;

	i = 0;
	while (i < *len)
	{
		i_key = isolate_key(inputs[i]);
		if (input_valid(env, inputs[i]) == 0
			|| check_tab_double(inputs, inputs[i]) == 1)
		{
			inputs = pop_unvalid_input(inputs, inputs[i], len, exit);
			i = 0;
			free(i_key);
			continue ;
		}
		free(i_key);
		++i;
	}
	return (inputs);
}

char	**delete_vars(char **env, char **inputs, size_t len)
{
	char	**res;
	char	**add;
	size_t	i;
	size_t	k;

	res = malloc(sizeof(char *) * ((len_list(env) - len) + 2));
	if (res == NULL)
		return (env);
	add = get_env_var_add(env, inputs);
	i = 0;
	k = 0;
	while (env[i + k])
	{
		if (ft_ptr_inlist(add, &env[i + k]) == 1)
			++k;
		else
		{
			res[i] = ft_strdup(env[i + k]);
			++i;
		}
	}
	res[i] = NULL;
	free(add);
	free_list(env);
	return (res);
}

bool	ft_unset(t_data *data)
{
	char	**inputs;
	size_t	len;
	bool	exit;

	exit = 0;
	if (data->arg == NULL || ft_strlen(data->arg) == 0)
		return (exit);
	inputs = ft_split(data->arg, ' ');
	if (inputs == NULL)
		return (1);
	len = len_list(inputs);
	inputs = check_inputs(data->env, inputs, &len, &exit);
	if (len == 0)
	{
		free_list(inputs);
		return (exit);
	}
	data->env = delete_vars(data->env, inputs, len);
	free_list(inputs);
	return (0);
}
