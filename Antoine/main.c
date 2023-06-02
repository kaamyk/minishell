/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:30:55 by anvincen          #+#    #+#             */
/*   Updated: 2023/06/02 10:03:24 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_env = NULL;

char	*get_line(char *str)
{
	char	*line;

	line = NULL;
	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline(str);
	if (line)
		add_history(line);
	return (line);
}

void	ft_read_line(char *line)
{
	if (ft_strchr(line, ';') != 0)
		ft_get_command2(line, ';');
	else if (ft_strchr(line, '|') != 0)
		ft_get_command2(line, '|');
	else
		ft_get_command(line);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;

	//ft_signal();
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
		line = get_line("$>");
		if (!line)
			break ;
		ft_read_line(line);
	}
}
