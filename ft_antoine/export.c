/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/08/23 15:13:57 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_double(char **env, char *in_k, char *in_v)
{
	char	*env_k;
	char	*env_v;
	size_t	i;

	i = 0;
	while (env[i])
	{
		env_k = isolate_key(env[i]);
		if (ft_strcmp(env_k, in_k) == 0)
		{
			env_v = isolate_value(env[i]);
			if (ft_strcmp(env_v, in_v) == 0)
			{
				free(env_k);
				free(in_v);
				free(env_v);
				return (0);
			}
			free(env_v);
		}
		free(env_k);
		++i;
	}
	free(in_v);
	return (1);
}

char	**add_variable(char **env, char *n_var)
{
	char	**n_env;
	size_t	i;

	printf("add_variable => n_var == %s\n", n_var);
	n_env = ft_calloc(len_list(env) + 2, sizeof(char *));
	if (n_env == NULL)
		return (NULL);
	i = 0;
	while (env[i])
	{
		n_env[i] = ft_strdup(env[i]);
		if (n_env[i] == NULL)
			break ;
		++i;
	}
	if (i > 0 && n_env[i - 1] != NULL)
		n_env[i] = ft_strdup(n_var);
	else
	{
		free_list(n_env);
		return (NULL);
	}
	n_env[i + 1] = NULL;
	free_list(env);
	return (n_env);
}

char	**replace_vl(char **env, char *o_var, char *n_var)
{
	char	**n_env;
	size_t	i;

	n_env = malloc(sizeof(char *) * (len_list(env) + 1));
	i = 0;
	while (env[i])
	{
		if (env[i] == o_var)
			n_env[i] = ft_strdup(n_var);
		else
			n_env[i] = ft_strdup(env[i]);
		if (n_env[i] == NULL)
		{
			free_list(n_env);
			return (env);
		}
		++i;
	}
	n_env[i] = NULL;
	free_list(env);
	return (n_env);
}

char	**handle_inputs(char **env, char **inputs, bool *exit)
{
	char	**i_keys;
	size_t	i;

	i_keys = get_keys(inputs);
	i = 0;
	while (inputs[i])
	{
		if (check_double(env, i_keys[i], isolate_value(inputs[i])) == 0)
		{
			if (get_var(env, i_keys[i], 1) != NULL)
				env = replace_vl(env, get_var(env, i_keys[i], 1), inputs[i]);
			else
			{
				env = add_variable(env, inputs[i]);
				if (env == NULL)
					break ;
			}
		}
		else
			*exit = 1;
		++i;
	}
	free_list(i_keys);
	return (env);
}

bool	ft_export(t_data *data)
{
	char	**inputs;
	bool	exit;

	printf("ft_export => data->arg == [%s]\n", data->arg);
	if (data->arg == NULL || ft_strlen(data->arg) == 0)
	{
		print_env(data->env, 1);
		return (0);
	}
	exit = 0;
	inputs = ft_split(data->arg, ' ');
	if (inputs == NULL)
		return (NULL);
	data->env = handle_inputs(data->env, inputs, &exit);
	free_list(inputs);
	if (data->env == NULL)
		return (1);
	return (exit);
}
