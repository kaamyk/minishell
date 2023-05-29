/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:54:54 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/25 13:55:57 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read_dir(DIR *dp)
{
	struct dirent	*dirp;

	errno = 0;
	while ((dirp = readdir(dp)) != NULL)
	{
		if (ft_strchr(dirp->d_name, '.') == 0
			&& ft_strncmp(dirp->d_name, "Makefile", ft_strlen(dirp->d_name)) != 0)
			printf(GREEN "%s " RESET, dirp->d_name);
		else
			printf("%s ", dirp->d_name);
	}
	printf("\n");

	if (errno != 0)
	{
		if (errno == EBADF)
			printf("Invalid directory stream descriptor\n");
		else
			perror("readdir");
	}
}

void	ft_check_dir(char *dir, int n)
{
	DIR	*dp;
	int	error;		

	error = 0;
	errno = 0;
	if ((dp = opendir(dir)) == NULL)
	{
		if (errno == EACCES)
		{
			printf("Permission denied\n");
			error = 1;
		}
		else if (errno == ENOENT)
		{
			printf("Directory does not exist\n");
			error = 1;
		}
		else if (errno == ENOTDIR)
		{
			printf("'%s' is not a directory\n", dir);
			error = 1;
		}
	}

	if (n == 1)
		ft_read_dir(dp);
	else if (error != 1)
		ft_error(DIRECTORY, dir, NULL);

	if (closedir(dp) == -1 && error != 1)
		perror("closedir");
}

int	ft_other_command(char *command)
{
	if (ft_strnstr(command, "ls", 2) != 0)
	{
		ft_check_dir(".", 1);
		return (1);
	}
	else if (ft_strchr(command, '/') != 0)
	{
		ft_check_dir(command, 2);
		return (1);
	}
	return (0);
}
