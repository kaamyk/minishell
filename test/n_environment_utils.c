/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_environment_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:30:55 by anvincen          #+#    #+#             */
/*   Updated: 2023/07/19 19:27:28 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*isolate_value(char *var)
{
	char	*res;
	size_t	len;
	size_t	r_sep;

	if (var == NULL || ft_strchr(var, '=') == 0)
		return (NULL);
	r_sep = rank_char(var, '=');
	len = ft_strlen(var) - r_sep;
	if (len == 0)
	{
		res = ft_calloc(1, 1);
		return (res);
	}
	else
		res = del_char(ft_substr(var, r_sep + 1, len + 1), '"');
	return (res);
}

char	**get_values(char **env)
{
	char	**res;
	size_t	i;

	res = malloc(sizeof(char *) * (len_list(env) + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		res[i] = isolate_value(env[i]);
		if (res[i] == NULL && ft_strchr(env[i], '=') != 0)
			return (NULL);
		++i;
	}
	res[i] = NULL;
	return (res);
}

char	*isolate_key(char *var)
{
	char	*res;
	size_t	rank;

	rank = rank_char(var, '=');
	res = malloc(rank + 1);
	ft_strlcpy(res, var, rank + 1);
	return (res);
}

char	**get_keys(char **env)
{
	char	**res;
	char	*env_k;
	size_t	i;

	if (env == NULL)
		return (NULL);
	res = malloc(sizeof(char *) * (len_list(env) + 1));
	i = 0;
	while (env[i])
	{
		res[i] = malloc(rank_char(env[i], '=') + 1);
		env_k = isolate_key(env[i]);
		ft_strlcpy(res[i], env_k, rank_char(env[i], '=') + 1);
		free(env_k);
		++i;
	}
	res[i] = NULL;
	return (res);
}

char	*get_var(char **env, char *var)
{
	char	*e_tmp;
	char	*v_key;
	size_t	i;

	v_key = isolate_key(var);
	i = 0;
	while (env[i])
	{
		e_tmp = isolate_key(env[i]);
		if (ft_strcmp(e_tmp, v_key) == 1)
		{
			free(e_tmp);
			return (env[i]);
		}
		free(e_tmp);
		++i;
	}
	free(v_key);
	return (NULL);
}
