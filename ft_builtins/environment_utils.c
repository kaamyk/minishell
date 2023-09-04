/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:30:55 by anvincen          #+#    #+#             */
/*   Updated: 2023/09/01 10:11:23 by anvincen         ###   ########.fr       */
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

void	print_line(char *key, char *val, bool a)
{
	if (a != 0)
	{
		if (val != NULL)
			printf("%s=\"%s\"\n", key, val);
		else
			printf("%s\n", key);
	}
	else if (val != NULL)
		printf("%s=%s\n", key, val);
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
		print_line(key[i], val, a);
		free(val);
		++i;
	}
	free_list(key);
	return (0);
}
