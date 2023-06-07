/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/07 18:41:15 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env;

size_t	print_var(char *s)
{
	size_t	i;

	i = 0;
	while (g_env->key[i])
	{
		if (ft_strncmp(g_env->key[i], s, ft_strlen(g_env->key[i])))
		{
			printf("%s\n", g_env->value[i]);
			break ;
		}
		++i;
	}
	return (i);
}

void	print_env(void)
{
	size_t	i;

	i = 0;
	while (g_env->key[i])
	{
		printf("%s=\"%s\"\n", g_env->key[i], g_env->value[i]);
		++i;
	}
}
