/* ************************************************************************** */                                                          
/*                                                                            */                                                          
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/29 11:23:18 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_export(char *command, char *arg)
{
	printf("Dans FT_EXPORT\n");
	static t_envvar	*envvar = NULL;
	char			*n_key;
	char			*n_value;

	(void) command;
	if (getenv(arg) != NULL)
	{
		printf("Dans le if\n");
		// Editer la variable d'environnement
	}
	else
	{
		// Editer une nouvelle variable;
	}
}

int	main(void)
{
	char	*s;

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
			ft_export("export", s + strlen("export "));
	}
	return (0);
}