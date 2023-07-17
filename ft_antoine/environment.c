/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:30:55 by anvincen          #+#    #+#             */
/*   Updated: 2023/07/17 18:55:01 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_var_rank(t_env *env, char *key)
{
	int	i;

	i = 0;
	while (env->key[i])
	{
		if (ft_strncmp(env->key[i], key, ft_strlen(env->key[i])) == 0)
			return (i);
		++i;
	}
	return (-1);
}

char	**init_keys(char **l, size_t len)
{
	char	**res;
	size_t	rank;
	size_t	i;

	if (l == NULL)
		return (NULL);
	i = 0;
	res = malloc(sizeof(char *) * (len + 1));
	while (l[i])
	{
		rank = rank_char(l[i], '=');
		res[i] = malloc(rank + 1);
		ft_strlcpy(res[i], l[i], rank + 1);
		++i;
	}
	res[i] = NULL;
	return (res);
}

char	*isolate_value(char *s)
{
	char	*res;
	size_t	len;
	size_t	r_sep;

	if (s == NULL || ft_strchr(s, '=') == 0)
		return (NULL);
	r_sep = rank_char(s, '=');
	len = ft_strlen(s) - r_sep;
	if (len == 0)
	{
		res = ft_calloc(1, 1);
		return (NULL);
	}
	else
		res = del_char(ft_substr(s, r_sep + 1, len + 1), '"');
	return (res);
}

char	**init_values(char **l)
{
	char	**res;
	size_t	i;

	res = malloc(sizeof(char *) * (len_list(l) + 1));
	if (res == NULL)
		return (free_all(NULL, l, NULL));
	i = 0;
	while (l[i] != NULL)
	{
		res[i] = isolate_value(l[i]);
		if (res[i] == NULL && ft_strchr(l[i], '=') != 0)
			return (NULL);
		++i;
	}
	res[i] = NULL;
	return (res);
}

t_env	*init_env(char **env)
{
	t_env	*n_env;
	char	*invalid;

	if (env == NULL)
		return (NULL);
	invalid = check_inputs(env);
	if (invalid != NULL)
	{
		printf("bash: export: '%s': not a valid identifier\n", invalid);
		free_list(env, len_list(env));
		return (NULL);
	}
	n_env = malloc(sizeof(t_env));
	if (n_env == NULL)
		return (free_all(NULL, env, NULL));
	n_env->env = dup_list(env);
	n_env->key = init_keys(env, len_list(env));
	n_env->value = init_values(env);
	if (n_env->key == NULL || n_env->value == NULL)
		return (free_all(n_env, env, NULL));
	return (n_env);
}
