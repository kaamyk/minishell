/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/13 15:46:58 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char *command, char *arg)
{
	size_t	i;
	size_t	j;

	(void)command;
	i = 0;
	while (arg[i] == ' ')
		++i;
	while (arg[i])
	{
		if (arg[i] == '"' || arg[i] == '\'')
		{
			j = 1;
			while (arg[i + j] && arg[i + j] != arg[i])
			{
				write(STDOUT_FILENO, &arg[i + j], 1);
				++j;
			}
			i += j;
		}
		else
			write(STDOUT_FILENO, &arg[i], 1);
		++i;
	}
	write (STDOUT_FILENO, "\n", 1);
}
