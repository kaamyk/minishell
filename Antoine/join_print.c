/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/14 19:58:36 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env;

char	*join_print(char *fd)
{
	char	*res;
	char	*buffer;
	char	*tmp;
	ssize_t	bytes;

	res = NULL;
	close(fd[1]);
	buffer = ft_calloc(1024, 1);
	while (1)
	{
		bytes = read(fd[0], buffer, sizeof(buffer));
		if (bytes <= 0)
			break ;
		if (res == NULL)
			res = ft_strdup(buffer);
		else
		{
			tmp = res;
			res = ft_strjoin(res, buffer);
			free(res);
		}
	}
	close(fd[0]);
	wait (NULL);
	return (res);
}

char	*read_print(char *f(bool), bool print)
{
	int		fd[2];

	if (print == true)
	{
		print_env(print);
		return (NULL);
	}
	pipe(fd);
	if (fork() == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		f(a);
		exit (0);
	}
	else
		return (join_env(fd));
}
