/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:00:35 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/26 17:05:18 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// int	main(void)
// {
// 	char	cmd[] = "/usr/bin/ls";

// 	//char	*argVec[] = {"ls", NULL};
// 	char	*argVec[] = {"ls", "-l", NULL};
// 	char	*envVec[] = {NULL};

// 	if (execve(cmd, argVec, envVec) == -1)
// 	{
// 		perror("error\n");
// 	}
// 	else
// 		printf("OK\n");
// 	return (0);
// }

/*********************************************/
// int	main(void)
// {
// 	char	*shell = "/bin/sh";
// 	char	*args[] = {"/bin/sh", NULL};
// 	char	*env[] = {NULL};

// 	execve(shell, args, env);
// 	exit(EXIT_FAILURE);
// }

/***********************************************/
#include <unistd.h>

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	// FILE	*fd;

	// fd = open(av[1], O_RDONLY);
	//printf("[%s]\n", av[1]);
	//char* argv[3] = {"/bin/cat", "/test/file", NULL};
	char* argv[4] = {"/bin/wc", "-l", av[1], NULL};
	execve(argv[0], argv, NULL);
	return (0);
}
