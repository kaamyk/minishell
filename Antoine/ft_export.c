/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/31 15:06:41 by antoine          ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	char	*s;

	(void) argc;
	(void) argv;
	g_env = dup_list(env);
	if (g_env == NULL)
	{
		printf("allocation failed");
		exit (errno);
	}
	while (1)
	{
		s = readline("$>");
		if (s == NULL)
		{
			free_list((void **) g_env);
			return (0);
		}
		printf("comp == %d\n", strncmp(s, "export", strlen("export")));
		// if (strcmp(s, "pwd") == 0)
		// 	ft_pwd();
		// if (strcmp(s, "cd") == 0)
		// 	ft_cd("cd", NULL);
		// else if (strncmp(s, "cd", 2) == 0)
		// 	ft_cd("cd", s + 3);
		if (strncmp(s, "export ", strlen("export ")) == 0)
			ft_export("export", s + strlen("export "));
		else if (strncmp(s, "export", strlen("export")) == 0)
			ft_export("export", NULL);
	}
	return (0);
}
