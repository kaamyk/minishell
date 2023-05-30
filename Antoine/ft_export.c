/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/30 12:28:07 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_env;

void	ft_export(char *command, char *arg)
{
	printf("Dans FT_EXPORT\n");
	char	**inputs;
	char	**n_env;
	char 	**tmp;
	size_t	i;
	size_t	j;

	(void) command;
	inputs = ft_split(arg, ' ');
	if (inputs == NULL)
		return ;
	if (getenv(arg) != NULL)
	{
		printf("Dans le if\n");
		// Editer la variable d'environnement
	}
	else
	{
		printf("Dans le else\n");
		// Editer une nouvelle variable;
		n_env = malloc((sizeof inputs) + sizeof g_enc + sizeof(char *));
		if (n_env == NULL)
			return ;
		while (g_env[i])
		{
			n_env[i] = ft_strdup(g_env[i]);
			if (n_env[i] == NULL)
			{
				perror("Allocation error");
				free_lst(n_env);
			}
			++i;
		}
		while (inputs[j])
		{
			n_env[i + j] = ft_strdup(inputs[j]);
			if (n_env[i + j] == NULL)
			{
				perror("Allocation error");
				free_lst(n_env);
			}
			++j;
		}
		n_env[i] = NULL;
		tmp = g_env;
		g_env = n_env;
		free_lst(tmp);
	}
	free_lst(inputs);
}

int	main(void)
{
	char	*s;

	g_env = malloc(sizeof(char *));
	if (g_env == NULL)
	{
		free(envvar);
		perror("allocation failed");
		exit (errno);
	}
	g_env[0] = NULL;
	while (1)
	{
		s = readline("$>");
		if (s == NULL)
			return (0);
		printf("cmp == %d\n", strcmp(s, "export"));
		// if (strcmp(s, "pwd") == 0)
		// 	ft_pwd();
		// if (strcmp(s, "cd") == 0)
		// 	ft_cd("cd", NULL);
		// else if (strncmp(s, "cd", 2) == 0)
		// 	ft_cd("cd", s + 3);
		if (strncmp(s, "export", strlen("export")) == 0)
			ft_export("export", s + strlen("export "),);
	}
	return (0);
}
