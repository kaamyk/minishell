/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/07 18:39:41 by antoine          ###   ########.fr       */
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

char	**init_values(char **l)
{
	printf("\t>>>INIT_VALUES<<<\n");
	char	**res;
	size_t	len;
	size_t	r_sep;
	size_t	i;

	len = len_list(l);
	res = malloc(sizeof(char *) * (len + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (l[i] != NULL)
	{
		r_sep = rank_char(l[i], '=');
		len = ft_strlen(l[i]) - r_sep;
		if (len == 0)
			res[i] = ft_calloc(1, 1);
		else
			res[i] = del_char(ft_substr(l[i], r_sep + 1, len + 1), '"');
		++i;
	}
	res[i] = NULL;
	return (res);
}

bool	check_double(char *key, char *value)
{
	printf("\t>>>CHECK_DOUBLE<<<\n");
	size_t	i;

	i = 0;
	while (g_env->key[i])
	{
		if (ft_strncmp(g_env->key[i], key, ft_strlen(g_env->key[i])) == 0)
		{
			if (ft_strlen(g_env->value[i]) != 0 && ft_strlen(value) == 0)
			{
				printf("Dans le if\n");
				return (1);
			}
			else if (ft_strncmp(g_env->value[i], value
					, ft_strlen(g_env->value[i])) == 0
				&& ft_strncmp(g_env->value[i], value, ft_strlen(value)) == 0)
			{
				printf("Dans le else if\n");
				return (1);
			}
		}
		++i;
	}
	return (0);
}

int	find_var_rank(char *key)
{
	int	i;

	i = 0;
	while (g_env->key[i])
	{
		if (ft_strncmp(g_env->key[i], key, ft_strlen(g_env->key[i])) == 0)
			return (i);
		++i;
	}
	return (-1);
}
