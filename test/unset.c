/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/20 10:26:44 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pop_unvalid_input(t_env *env, size_t r, size_t *len, bool *exit)
{
	size_t	j;

	*exit = 1;
	j = r + 1;
	while (j < *len)
	{
		env->key[j - 1] = env->key[j];
		env->value[j - 1] = env->value[j];
		++j;
	}
	env->key[j] = NULL;
	env->value[j] = NULL;
	--(*len);
}

bool	is_to_pop(t_env *env, t_env *tmp, size_t r)
{
	char	*k;
	char	*v;
	size_t	i;

	v = env->value[r];
	k = env->key[r];
	i = 0;
	while (tmp->key[i])
	{
		if (ft_strncmp(k, tmp->key[i], ft_strlen(k)) == 0
			&& ft_strncmp(k, tmp->key[i], ft_strlen(tmp->key[i])) == 0)
		{
			if (tmp->value[i] == NULL)
				return (1);
			else if ((v != NULL && tmp->value[i] != NULL)
				&& ft_strncmp(v, tmp->value[i], ft_strlen(tmp->value[i])) == 0
				&& ft_strncmp(v, tmp->value[i], ft_strlen(v) == 0))
				return (1);
		}
		++i;
	}
	return (0);
}

char	**delete_items(t_env *env, t_env *n_env, t_env *tmp, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i + j < len)
	{
		if (is_to_pop(env, tmp, i + j) == 0)
		{
			n_env->key[i] = ft_strdup(env->key[i + j]);
			if (env->value[i + j] != NULL)
				n_env->value[i] = ft_strdup(env->value[i + j]);
			else
				n_env->value[i] = NULL;
			++i;
		}
		else
			++j;
	}
	free_env(tmp);
	n_env->key[i] = NULL;
	n_env->value[i] = NULL;
	free_env(env);
	env = n_env;
	return (env->key);
}

size_t	get_inputs(t_env *env, t_env *tmp, size_t len, bool *exit)
{
	size_t	i;

	i = 0;
	while (tmp->key[i])
	{
		if (input_valid(env, tmp->key[i], tmp->value[i], len) != 0)
			pop_unvalid_input(tmp, i, &len, exit);
		++i;
	}
	return (len);
}

bool	ft_unset(t_env *env, char *arg)
{
	t_env	*n_env;
	t_env	*inputs;
	size_t	len;
	bool	exit;

	exit = 0;
	inputs = init_env(ft_split(arg, ' '));
	if (inputs == NULL)
		return (!exit);
	len = get_inputs(env, inputs, len_list(inputs->key), &exit);
	if (len == 0)
		return (exit);
	n_env = malloc(sizeof(t_env));
	if (n_env == NULL)
		return (free_all(inputs, NULL, NULL));
	len = len_list(env->key) - len;
	n_env->key = malloc(sizeof(char *) * (len + 1));
	n_env->value = malloc(sizeof(char *) * (len + 1));
	if (n_env->key == NULL || n_env->value == NULL)
	{
		free_env(n_env);
		return (free_all(inputs, NULL, NULL));
	}
	delete_items(env, n_env, inputs, len_list(env->key));
	return (exit);
}
