/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:30:55 by anvincen          #+#    #+#             */
/*   Updated: 2023/06/08 11:35:56 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env;

bool	check_double(char *key, char *value)
{
	printf("\t>>>CHECK_DOUBLE<<<\n");
	size_t	l_value;
	size_t	l_val_env;
	size_t	i;

	i = 0;
	while (g_env->key[i])
	{
		if (ft_strncmp(g_env->key[i], key, ft_strlen(g_env->key[i])) == 0)
		{
			l_val_env = ft_strlen(g_env->value[i]);
			l_value = ft_strlen(value);
			if (l_val_env != 0 && l_value == 0)
				return (1);
			else if (ft_strncmp(g_env->value[i], value, l_val_env) == 0
				&& ft_strncmp(g_env->value[i], value, l_value) == 0)
				return (1);
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
		if (g_env->value[i] != NULL)
			printf("%s=\"%s\"\n", g_env->key[i], g_env->value[i]);
		else
			printf("%s\n", g_env->key[i]);
		++i;
	}
}
