/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/07 11:11:43 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_env	*g_env;

bool	add_variable(char **n_key, char **n_value)
{
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

bool	handle_inputs(t_env *res, bool *exit)
{
	size_t	i;

	i = 0;
	while (res->key[i])
	{
		if (check_double(res->key[i], res->value[i]) == 0)
		{
			if (find_var_rank(res->key[i]) >= 0)
			{
				if (replace_value(res->value[i],
						find_var_rank(res->key[i])) != 0)
					return (1);
			}
			else
				if (add_variable(&res->key[i], &res->value[i]) != 0)
					return (1);
		}
		else
			*exit = 1;
		++i;
	}
	return (0);
}

bool	ft_export(t_data *data)
{
	t_env	*res;
	bool	exit;

	exit = 0;
	if (data->arg == NULL || ft_strlen(data->arg) == 0)
		return (print_env(1));
	res = init_env(ft_split(data->arg, ' '));
	if (res == NULL)
		return (1);
	if (handle_inputs(res, &exit) != 0)
		return (1);
	free_env(res);
	// printf("\t|=>Fin &g_env->key == ");
	// print_list(g_env->key);
	return (exit);
}
