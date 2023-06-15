/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/15 11:52:26 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env;

char	*join_print(int *fd)
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
		tmp = res;
		if (bytes <= 0)
			break ;
		if (res == NULL)
			res = ft_strdup(buffer);
		else
		{
			res = ft_strjoin(res, buffer);
			free(tmp);
		}
	}
	free(buffer);
	close(fd[0]);
	wait (NULL);
	return (res);
}

char	*read_print(bool (*f)(char *), char *arg, bool print)
{
	int		fd[2];
	//fd[0] read
	//fd[1] write

	if (print == true)
	{
		f(arg);
		return (NULL);
	}
	pipe(fd);
	if (fork() == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		f(arg);
		exit (0);
	}
	else
		return (join_print(fd));
}
