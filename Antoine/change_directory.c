/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/25 17:43:48 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_nb_args(char *command)
{
	size_t	i;

	i = 2;
	while (command[i] && command[i] == ' ')
		++i;
	while (command[i] && command[i] != ' ')
		++i;
	while (command[i] && command[i] == ' ')
		++i;
	if (command[i])
		return (true);
	return (false);
}

void	ft_cd(char *line)
{
	if (check_nb_args(line) != 0)
	{
		printf(">>> Too many args <<<\n");
		return ;
	}
	else
	{
		printf("size == 2\n");
		printf("result == %d\n", ft_quotes(line));
		if (ft_check_open_quotes(line) == 0)
			printf("Error\n");
		return ;
	}
	// else if args == 1 (line == "cd") => cd home/
}
