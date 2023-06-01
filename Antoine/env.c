/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/01 11:04:24 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	print_env(char *var, char **g_env)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (g_env[i])
	{
		j = 0;
		while (var[j] && var[j] != ' ' && g_env[i][j]
			&& var[j + 1] == g_env[i][j] && g_env[i][j] != '=')
			++j;
		if (g_env[i][j] == '=')
		{
			if (ft_strncmp(var + 1, g_env[i], j) == 0)
			{
				ft_putstr_fd(g_env[i] + j + 1, STDOUT_FILENO);
				return (j);
			}
		}
		++i;
	}
	return (0);
}

// size_t	print_env(char *var, char **g_env)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	while (g_env[i])
// 	{
// 		if (ft_strncmp(var, g_env[i], ft_strlen(var)) == 0)
			
// 	}
// 	return (0);
// }
