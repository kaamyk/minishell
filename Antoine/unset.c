/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/13 15:28:00 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env;

bool	input_valid(char *key, char *value, size_t len)
{
	int		r;
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (key[ft_strlen(key) - 1] != '=')
		{
			r = find_var_rank(key);
			if (r == -1)
				return (1);
			if (value != NULL && g_env->value[r] != NULL
				&& ft_strncmp(g_env->value[r], value, ft_strlen(g_env->value[r]))
				&& ft_strncmp(g_env->value[r], value, ft_strlen(value)))
				return (1);
		}
		++i;
	}
	return (0);
}

void	pop_unvalid_input(t_env *env, size_t r, size_t *len)
{
	size_t	j;

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

bool	is_to_pop(t_env *tmp, size_t r)
{
	size_t	i;

	i = 0;
	while (tmp->key[i])
	{
		if (ft_strncmp(g_env->key[r], tmp->key[i], ft_strlen(tmp->key[i])) == 0
			&& ft_strncmp(g_env->key[r], tmp->key[i], ft_strlen(tmp->key[i])) == 0)
		{
			if (tmp->value[i] == NULL)
				return (1);
			if ((g_env->value[r] != NULL && tmp->value[i] != NULL)
				&& (ft_strncmp(g_env->value[r], tmp->value[i], ft_strlen(tmp->key[i]) == 0)
					&& ft_strncmp(g_env->value[r], tmp->value[i], ft_strlen(g_env->value[r])) == 0))
				return (1);
		}
		++i;
	}
	return (0);
}

char	**delete_items(t_env *n_env, t_env *tmp, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i + j < len)
	{
		if (is_to_pop(tmp, i + j) == 0)
		{
			n_env->key[i] = ft_strdup(g_env->key[i + j]);
			if (g_env->value[i + j] != NULL)
				n_env->value[i] = ft_strdup(g_env->value[i + j]);
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
	free_env(g_env);
	g_env = n_env;
	return (g_env->key);
}

void	ft_unset(char *command, char *arg)
{
	printf("\t>>>FT_UNSET<<<\n");
	t_env	*n_env;
	t_env	*tmp;
	size_t	len;
	size_t	i;

	(void)command;
	tmp = init_env(ft_split(arg, ' '));
	if (tmp == NULL)
		return ;
	len = len_list(tmp->key);
	i = 0;
	while (tmp->key[i])
	{
		if (input_valid(tmp->key[i], tmp->value[i], len) != 0)
			pop_unvalid_input(tmp, i, &len);
		++i;
	}
	if (len == 0)
		return ;
	n_env = malloc(sizeof(t_env));
	len = len_list(g_env->key) - len;
	n_env->key = malloc(sizeof(char *) * (len + 1));
	n_env->value = malloc(sizeof(char *) * (len + 1));
	delete_items(n_env, tmp, len_list(g_env->key));
}
