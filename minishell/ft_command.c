/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/23 15:26:23 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	cwd[10000];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
	}
	else
	{
		perror("ft_pwd() error");
		return ;
	}
}

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

void	ft_determine_command(char *command)
{
	//printf("--> %s %ld\n", command, ft_strlen(command));
	if (ft_strncmp(command, "exit", ft_strlen(command)) == 0)
	{
		printf("%s\n", command);
		exit(0);
	}
	else if (ft_strncmp(command, "pwd", ft_strlen(command)) == 0)
	{
		ft_pwd();
	}
	else if (ft_strncmp(command, "ls", ft_strlen(command)) == 0)
	{
		ft_check_dir(".", 1);
	}
	else
	{
		ft_error(NOT_FOUND, command, NULL);
	}
		
}
