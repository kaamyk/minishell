/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:30:55 by anvincen          #+#    #+#             */
/*   Updated: 2023/07/19 15:48:44 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	input_valid(t_env *env, char *key, char *value, size_t len)
{
	char	*v;
	int		r;
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (key[ft_strlen(key) - 1] != '=')
		{
			r = find_var_rank(env, key);
			if (r == -1)
				return (1);
			v = env->value[r];
			if (value != NULL && v != NULL
				&& ft_strncmp(v, value, ft_strlen(v) != 0)
				&& ft_strncmp(v, value, ft_strlen(value)) != 0)
				return (1);
		}
		++i;
	}
	return (0);
}

bool	check_double(t_env *env, char *key, char *value)
{
	size_t	l_value;
	size_t	l_val_env;
	size_t	i;

	l_value = 0;
	if (value != NULL)
		l_value = ft_strlen(value);
	i = 0;
	while (env->key[i])
	{
		if (ft_strncmp(env->key[i], key, ft_strlen(env->key[i])) == 0)
		{
			l_val_env = 0;
			if (env->value[i] != NULL)
				l_val_env = ft_strlen(env->value[i]);
			if ((l_val_env != 0 && l_value == 0) || (env->value[i] != NULL
					&& ft_compare_str(env->value[i], value) == 0))
				return (1);
		}
		++i;
	}
	return (0);
}

size_t	print_var(t_env *env, char *var)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(var);
	i = 0;
	while (env->key[i])
	{
		if (ft_strncmp(env->key[i], var, ft_strlen(env->key[i])) == 0
			&& ft_strncmp(env->key[i], var, ft_strlen(var)) == 0)
		{
			write(1, env->value[i], ft_strlen(env->value[i]));
			break ;
		}
		++i;
	}
	free(var);
	return (len);
}

bool	print_env(t_env *env, bool a)
{
	size_t	i;

	i = 0;
	while (env->key[i])
	{
		if (a == 0)
		{
			if (env->value[i] != NULL)
				printf("%s=\"%s\"\n", env->key[i], env->value[i]);
			else
				printf("%s\n", env->key[i]);
		}
		else if (a != 0)
		{
			if (env->value[i] != NULL)
				printf("declare -x %s=\"%s\"\n", env->key[i], env->value[i]);
			else
				printf("declare -x %s\n", env->key[i]);
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
