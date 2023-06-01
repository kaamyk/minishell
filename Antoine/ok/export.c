/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/31 15:10:06 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_env = NULL;

void	ft_export(char *command, char *arg)
{
	char	**inputs;
	char	**n_env;
	char	**tmp;

	(void) command;
	inputs = ft_split(arg, ' ');
	if (arg == NULL)
	{
		printf("Dans le else print_list\n");
		print_list(g_env);
		return ;
	}
	n_env = join_list(g_env, inputs);
	free_list((void **) inputs);
	if (n_env == NULL)
		return ;
	tmp = g_env;
	g_env = n_env;
	free_list((void **)tmp);
}
