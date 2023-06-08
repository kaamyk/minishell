/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:30:55 by anvincen          #+#    #+#             */
/*   Updated: 2023/06/08 16:41:13 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env;

char	**init_keys(char **l, size_t len)
{
	printf("\t>>>INIT_KEYS<<<\n");
	char	**res;
	size_t	rank;
	size_t	i;

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
		res = ft_calloc(1, 1);
	else
		res = del_char(ft_substr(s, r_sep + 1, len + 1), '"');
	return (res);
}

char	**init_values(char **l)
{
	printf("\t>>>INIT_VALUES<<<\n");
	char	**res;
	size_t	i;

	res = malloc(sizeof(char *) * (len_list(l) + 1));
	if (res == NULL)
		return (NULL);
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

	if (env == NULL)
		return (NULL);
	n_env = malloc(sizeof(t_env));
	n_env->key = init_keys(env, len_list(env));
	n_env->value = init_values(env);
	if (g_env != NULL)
		free_list(env, len_list(env));
	return (n_env);
}
