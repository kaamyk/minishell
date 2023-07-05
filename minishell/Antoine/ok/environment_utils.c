/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:30:55 by anvincen          #+#    #+#             */
/*   Updated: 2023/06/21 18:20:40 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env;

bool	check_double(char *key, char *value)
{
	size_t	l_value;
	size_t	l_val_env;
	size_t	i;

	l_value = 0;
	if (value != NULL)
		l_value = ft_strlen(value);
	i = 0;
	while (g_env->key[i])
	{
		if (ft_strncmp(g_env->key[i], key, ft_strlen(g_env->key[i])) == 0)
		{
			l_val_env = 0;
			if (g_env->value[i] != NULL)
				l_val_env = ft_strlen(g_env->value[i]);
			if ((l_val_env != 0 && l_value == 0)
				|| (g_env->value[i] != NULL
					&& ft_strncmp(g_env->value[i], value, l_val_env) == 0
					&& ft_strncmp(g_env->value[i], value, l_value) == 0))
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

size_t	print_var(char *var)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(var);
	i = 0;
	while (g_env->key[i])
	{
		if (ft_strncmp(g_env->key[i], var, ft_strlen(g_env->key[i])) == 0
			&& ft_strncmp(g_env->key[i], var, ft_strlen(var)) == 0)
		{
			write(1, g_env->value[i], ft_strlen(g_env->value[i]));
			break ;
		}
		++i;
	}
	free(var);
	return (len);
}

bool	print_env(bool a)
{
	size_t	i;

	i = 0;
	while (g_env->key[i])
	{
		if (a == 0)
		{
			if (g_env->value[i] != NULL)
				printf("%s=\"%s\"\n", g_env->key[i], g_env->value[i]);
			else
				printf("%s\n", g_env->key[i]);
		}
		else if (a != 0)
		{
			if (g_env->value[i] != NULL)
				printf("declare -x %s=\"%s\"\n", g_env->key[i], g_env->value[i]);
			else
				printf("declare -x %s\n", g_env->key[i]);
		}
		++i;
	}
	return (0);
}

char	*check_inputs(char **l)
{
	size_t	i;

	i = 0;
	while (l[i])
	{
		if (l[i][0] == '=')
			return (l[i]);
		++i;
	}
	return (NULL);
}
