/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:47:39 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/25 16:49:43 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_write_file(char *command, char *file)
{
	int fd;

	fd = open(file, O_CREAT|O_TRUNC|O_WRONLY, 0644);
	if (fd < 0) {
		perror(file);
		return (1);
	}

	dup2(fd, 1); 
	printf("%s\n", command);
	close(fd);
	return (0);
}

int	ft_redirections(char *str)
{
	static char	*line = NULL;

	if (!line)
		line = str;
	else if (line)
	{
		//printf("%s %s\n", line, str);
		ft_write_file(line, str);
		line = 0;
	}
	return (0);
}

/*
< file command
*/
// int	main(int ac, char **av)
// {
// 	if (ac == 3)
// 	{
// 		ft_redirections(av[1]);
// 		ft_redirections(av[2]);
// 	}
// 	return (0);
// }
