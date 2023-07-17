/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/17 18:29:41 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	add_variable(char **n_key, char **n_value, t_env *env, char **full_vl)
{
	size_t	len_env;
	char	**tmp;

	if (full_vl == NULL)
		return (1);
	len_env = len_list(env->key);
	tmp = env->env;
	env->env = join_list(env->env, full_vl, len_env, 1);
	if (env == NULL)
		return (1);
	free_list(tmp, len_env);
	tmp = env->key;
	env->key = join_list(env->key, n_key, len_env, 1);
	if (env->key == NULL)
		return (1);
	free_list(tmp, len_env);
	tmp = env->value;
	env->value = join_list(env->value, n_value, len_env, 1);
	if (env->value == NULL)
		return (1);
	free_list(tmp, len_env);
	return (0);
}

bool	replace_value(t_env *env, char *n_value, int r)
{
	char	*tmp;

	if (r < 0)
		return (1);
	tmp = env->value[r];
	env->value[r] = ft_strdup(n_value);
	if (env->value[r] == NULL)
	{
		free_all(NULL, NULL, tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

bool	handle_inputs(t_env *env, t_env *res, bool *exit)
{
	size_t	i;
	char	*s_tmp;

	i = 0;
	while (res->key[i])
	{
		if (check_double(env, res->key[i], res->value[i]) == 0)
		{
			if (res->value[i] != NULL)
				s_tmp = ft_strjoin(res->key[i], res->value[i]);
			else
				s_tmp = res->key[i];
			if (replace_value(env, res->value[i],
					find_var_rank(env, res->key[i])) != 0)
				return (1);
			else
				if (add_variable(&res->key[i], &res->value[i],
						env, &s_tmp) != 0)
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
		return (print_env(data->s_env, 1));
	res = init_env(ft_split(data->arg, ' '));
	if (res == NULL)
		return (1);
	if (handle_inputs(data->s_env, res, &exit) != 0)
		return (1);
	free_env(res);
	return (exit);
}
