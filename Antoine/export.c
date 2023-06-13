/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/13 15:33:45 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env;

bool	add_variable(char **n_key, char **n_value)
{
	printf("\t>>>ADD_VARIABLE<<<\n");
	size_t	len_env;
	char	**tmp;

	len_env = len_list(g_env->key);
	tmp = g_env->key;
	g_env->key = join_list(g_env->key, n_key, len_env, 1);
	if (g_env->key == NULL)
		return (1);
	free_list(tmp, len_env);
	tmp = g_env->value;
	g_env->value = join_list(g_env->value, n_value, len_env, 1);
	if (g_env->value == NULL)
		return (1);
	free_list(tmp, len_env);
	return (0);
}

bool	replace_value(char *n_value, size_t r)
{
	printf("\t>>>REPLACE_VALUE<<<\n");
	char	*tmp;

	tmp = g_env->value[r];
	g_env->value[r] = ft_strdup(n_value);
	if (g_env->value[r] == NULL)
	{
		free_all(NULL, NULL, tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

bool	ft_export(char *arg)
{
	printf("\t>>>FT_EXPORT<<<\n");
	t_env	*res;
	size_t	i;

	if (arg == NULL)
		return (print_env());
	res = init_env(ft_split(arg, ' '));
	if (res == NULL)
		return (1);
	i = 0;
	while (res->key[i])
	{
		if (check_double(res->key[i], res->value[i]) == 0)
		{
			if (find_var_rank(res->key[i]) >= 0
				&& (replace_value(res->value[i],
						find_var_rank(res->key[i])) != 0))
				return (1);
			else
				if (add_variable(&res->key[i], &res->value[i]) != 0)
					return (1);
		}
		++i;
	}
	free_env(res);
	return (0);
}
