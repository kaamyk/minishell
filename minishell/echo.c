/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/26 09:58:09 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char *arg)
{
	printf("Dans ft_echo\n");
	size_t	i;

	i = 0;
	//printf("Apres skip i == %ld\n", i);
	while (arg[i])
	{
		if (arg[i] == '"')
			++i;
		write(STDOUT_FILENO, &arg[i], 1);
		if (arg[i])
			++i;
	}
	write (STDOUT_FILENO, "\n", 1);
}
