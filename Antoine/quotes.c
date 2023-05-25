/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:15:47 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/25 15:12:42 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_check_open_quotes(char **command)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	len = ft_strlen(command[1]);
	while (i < len)
	{
		if (command[1][i] == '\'' || command[1][i] == '"')
		{
			j = i + 1;
			while (j < len)
			{
				if (command[1][j] == command[1][i])
				{
					i = j;
					break ;
				}
				++j;
			}
			if (j == len)
			{
				printf(">>> OPEN QUOTES <<<\n");
				return (NULL);
			}
		}
		++i;
	}
	printf(">>> QUOTES ARE CLOSED <<<\n");
	return (*command);
}

char	*ft_quotes(char **command)
{
	char	*tmp;
	char	*str;
	size_t	len;

	len = ft_strlen(command[1]);
	if (check_first_last_quotes(command[1], len) == true
		&& check_open_quotes(command[1], f_q) == true)
	{
		printf("check_quotes == %ld\n", check_open_quotes(command[1], f_q));
		return (command[1]);
	}
	else if (check_open_quotes(arg, '\'') == false
		|| check_open_quotes(arg, '"') == false)
		return (NULL);
	printf("check_quotes == %ld\n", check_open_quotes(command[1], f_q));
	return (command[1]);
}
