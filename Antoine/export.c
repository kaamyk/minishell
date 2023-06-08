/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/08 12:10:35 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env;

void	add_variable(char **n_key, char **n_value)
{
	printf("\t>>>ADD_VARIABLE<<<\n");
	size_t	len_env;
	size_t	len;

	len_env = len_list(g_env->key);
	len = len_list(n_key);
	g_env->key = join_list(g_env->key, n_key, len_env, len);
	g_env->value = join_list(g_env->value, n_value, len_env, len);
}

void	replace_value(char *n_value, size_t r)
{
	printf("\t>>>REPLACE_VALUE<<<\n");
	char	*tmp;

	tmp = g_env->value[r];
	g_env->value[r] = ft_strdup(n_value);
	printf("g_env->value[%ld] = %s\n", r, g_env->value[r]);
	free(tmp);
}

void	ft_export(char *command, char *arg)
{
	t_env	*res;
	size_t	i;

	(void) command;
	if (arg == NULL)
	{
		print_env();
		return ;
	}
	res = init_env(ft_split(arg, ' '));
	if (res == NULL)
		return ;
	i = 0;
	while (res->key[i])
	{
		if (check_double(res->key[i], res->value[i]) == 0)
		{
			if (find_var_rank(res->key[i]) >= 0)
				replace_value(res->value[i], find_var_rank(res->key[i]));
			else
				add_variable(&res->key[i], &res->value[i]);
		}
		++i;
	}
	printf("\t>>>FIN EXPORT<<<\n");
}
