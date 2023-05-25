/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/25 17:38:12 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char *command)
{
	printf("Dans ft_echo\n");
	size_t	i;

	i = 4;
	while (command[i] == ' ')
		++i;
	printf("Apres skip i == %ld\n", i);
	while (command[i])
	{
		if (command[i] == '"')
			++i;
		write(STDOUT_FILENO, &command[i], 1);
		++i;
	}
	write (STDOUT_FILENO, "\n", 1);
}
