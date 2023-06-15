/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/13 15:46:30 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env;

void	free_ptr(char *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_list(char **lst, size_t len)
{
	size_t	i;

	if (lst != NULL)
	{
		i = 0;
		while (i < len)
		{
			free_ptr(lst[i]);
			++i;
		}
	}
	free(lst);
	lst = NULL;
}

void	free_env(t_env *env)
{
	if (env == NULL)
		return ;
	if (env->value != NULL)
		free_list(env->value, len_list(env->key));
	if (env->key != NULL)
		free_list(env->key, len_list(env->key));
	free(env);
}

void	*free_all(t_env *e, char **l, char *s)
{
	if (e != NULL)
		free_env(e);
	if (l != NULL)
		free_list(l, len_list(l));
	if (s != NULL)
		free(s);
	if (g_env != NULL)
		free_env(g_env);
	return (NULL);
}
