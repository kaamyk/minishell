/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/01 08:18:51 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_nb_args(const char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i] == ' ')
		++i;
	while (arg[i])
	{
		if (arg[i] == ' ')
		{
			while (arg[i] == ' ' && arg[i + 1])
			{
				if (arg[i + 1] != ' ')
					return (true);
				++i;
			}
		}
		++i;
	}
	return (false);
}

void	ft_cd(char *command, const char *arg)
{
	(void)command;
	if (arg != NULL && check_nb_args(arg) != 0)
	{
		printf(">>> Too many args <<<\n");
		return ;
	}
	else
	{
		printf(">>> Args OK <<<\n");
		if (arg == NULL)
		{
			if (chdir(getenv("HOME")) != 0)
			{
				perror("chdir error :");
				return ;
			}		
		}
		else if (chdir(arg) != 0)
		{
			perror("chdir error :");
			return ;
		}
	}
}

// int	main(void)
// {
// 	char	*s;

// 	while (1)
// 	{
// 		s = readline("$>");
// 		if (s == NULL)
// 			return (0);
// 		printf("cmp == %d\n", strcmp(s, "cd"));
// 		if (strcmp(s, "pwd") == 0)
// 			ft_pwd();
// 		if (strcmp(s, "cd") == 0)
// 			ft_cd("cd", NULL);
// 		else if (strncmp(s, "cd", 2) == 0)
// 			ft_cd("cd", s + 3);
// 	}
// 	return (0);
// }
