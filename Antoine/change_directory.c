/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/24 20:35:04 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	nb_args(char **command)
{
	size_t	size;

	size = 0;
	while (command[size])
		++size;
	return (size);
}

void	ft_cd(char **command)
{
	size_t	size;

	size = nb_args(command);
	if (size > 3)
	{
		perror("cd: too many arguments");
		return ;
	}
	else if (size == 3)
	{
		printf("size == 3\n");
		printf("cd: string not in pwd: %s\n", command[1]);
		return ;
	}
	else if (size == 2)
	{
		printf("size == 2\n");
		printf("result == %s\n", ft_quotes(command));
		if (ft_quotes == NULL)
			printf("Error\n");
		return ;
	}
	else
	{
		printf("size == 1\n");
		return ;
	}
}
