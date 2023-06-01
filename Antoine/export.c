/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/01 17:22:32 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**g_env;

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

char	**format_env(char **inputs)
{
	char	*tmp;
	size_t	i;

	tmp = NULL;
	i = 0;
	while (inputs[i])
	{
		if (ft_strchr(inputs[i], '=')
			&& (ft_strchr(inputs[i], '"') == 0
				|| ft_strchr(inputs[i], '\'') == 0))
		{
			tmp = inputs[i];
			inputs[i] = join_quotes(inputs[i]);
		}
		if (tmp != NULL)
			free(tmp);
		++i;
	}
	return (inputs);
}

void	ft_export(char *command, char *arg)
{
	char	**inputs;
	char	**n_env;
	char	**tmp;

	(void) command;
	if (arg == NULL)
	{
		print_list(g_env);
		return ;
	}
	inputs = format_env(ft_split(arg, ' '));
	n_env = join_list(g_env, inputs);
	free_list((void **) inputs);
	if (n_env == NULL)
		return ;
	tmp = g_env;
	g_env = n_env;
	free_list((void **)tmp);
}
