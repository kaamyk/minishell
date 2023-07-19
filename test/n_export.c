/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/19 19:29:03 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

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
			free(env_k);
			env_v = isolate_value(env[i]);
			if (ft_strcmp(env_v, in_v) == 0)
			{
				free(env_v);
				return (0);
			}
			free(env_v);
		}
		++i;
	}
	free(in_k);
	free(in_v);
	return (1);
}

char	**add_variable(char **env, char *n_var)
{
	char	**n_env;
	size_t	i;

	printf(">>>add_variable\n");
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

char	**replace_value(char **env, char *o_var, char *n_var)
{
	char	**n_env;
	size_t	i;
	size_t	j;

	printf(">>>replace_value\n");
	printf("\t|=>o_var == %s\n", o_var);
	printf("\t|=>n_var == %s\n", n_var);
	n_env = malloc(sizeof(char *) * len_list(env) + 1);
	i = 0;
	j = 0;
	while (env[i + j])
	{
		if (env[i + j] == o_var)
		{
			n_env[i] = ft_strdup(n_var);
			++j;
		}
		else
			n_env[i] = ft_strdup(env[i + j]);
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
	char	**i_vals;
	size_t	i;

	i_keys = get_keys(inputs);
	i_vals = get_values(inputs);
	i = 0;
	while (inputs[i])
	{
		printf("handle_inputs => i == %ld\n", i);
		if (check_double(env, i_keys[i], i_vals[i]) == 0)
		{
			if (get_var(env, i_keys[i]) != NULL)
				env = replace_value(env, get_var(env, i_keys[i]), inputs[i]);
			else
			{
				env = add_variable(env, inputs[i]);
				if (env == NULL)
					break ;
			}
		}
		else
		{
			printf("Dans le else double\n");
			*exit = 1;
		}
		++i;
	}
	free_list(i_keys);
	free_list(i_vals);
	return (env);
}

bool	ft_export(t_data *data)
{
	char	**inputs;
	bool	exit;

	if (data->arg == NULL || ft_strlen(data->arg) == 0)
	{
		print_list(data->env);
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
