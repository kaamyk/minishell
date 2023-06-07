/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/07 18:37:03 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env;

void	add_variable(char **n_key, char **n_value)
{
	printf("\t>>>ADD_VARIABLE<<<\n");
	g_env->key = join_list(g_env->key, n_key);
	g_env->value = join_list(g_env->value, n_value);
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

char	*isolate_value(char *s)
{
	char	*res;
	size_t	len;
	size_t	rank_sep;
	size_t	i;

	if (s == NULL)
		return (NULL);
	res = NULL;
	rank_sep = rank_char(s, '=');
	len = ft_strlen(s) - (rank_sep + 1);
	res = malloc(len + 1);
	if (res == NULL)
		return (NULL);
	i = 1;
	while (s[rank_sep + i])
	{
		res[i - 1] = s[rank_sep + i];
		++i;
	}
	res[i - 1] = 0;
	return (res);
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
