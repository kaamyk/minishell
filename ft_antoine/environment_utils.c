/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:30:55 by anvincen          #+#    #+#             */
/*   Updated: 2023/07/27 15:09:26 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_ptr_inlist(char **l, char **ptr)
{
	size_t	i;

	i = 0;
	while (l[i])
	{
		if (l[i] == *ptr)
			return (1);
		++i;
	}
	return (0);
}

bool	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if ((s1 == NULL) ^ (s2 == NULL))
		return (false);
	else if (s1 == NULL && s1 == NULL)
		return (true);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (false);
		i++;
	}
	if (s1[i] == 0 && s2[i] == 0)
		return (true);
	else
		return (false);
}

char	*check_export_inputs(char **var)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (var[i])
	{
		if (ft_isalpha(var[i][0]) == 0 && var[i][0] != '_')
			return (var[i]);
		j = 1;
		while (var[i][j])
		{
			if (ft_isalnum(var[i][j]) == 0 && var[i][j] != '_')
				return (var[i]);
			++j;
		}
		++i;
	}
	return (NULL);
}

bool	print_env(char **env, bool a)
{
	char	**key;
	char	*val;
	size_t	i;

	key = get_keys(env);
	i = 0;
	while (key[i])
	{
		val = isolate_value(env[i]);
		if (a != 0)
			printf("declare -x ");
		if (ft_strlen(val) != 0)
			printf("%s=\"%s\"\n", key[i], val);
		else
			printf("%s\n", key[i]);
		free(val);
		++i;
	}
	free_list(key);
	return (0);
}

size_t	print_var(char **env, char *var)
{
	char	*tmp;
	size_t	len;
	size_t	i;

	i = 0;
	while (env[i])
	{
		tmp = isolate_key(env[i]);
		if (ft_strcmp(tmp, var) == 1)
		{
			free(tmp);
			tmp = isolate_value(env[i]);
			printf("%s", tmp);
			free(tmp);
			break ;
		}
		free(tmp);
		++i;
	}
	len = ft_strlen(var);
	free(var);
	return (len);
}
