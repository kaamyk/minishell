/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:15:47 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/25 17:11:56 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_check_open_quotes(char *line)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	len = ft_strlen(line);
	while (i < len)
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			j = i + 1;
			while (j < len)
			{
				if (line[j] == line[i])
				{
					i = j;
					break ;
				}
				++j;
			}
			if (j == len)
			{
				//printf(">>> OPEN QUOTES <<<\n");
				return (true);
			}
		}
		++i;
	}
	//printf(">>> QUOTES ARE CLOSED <<<\n");
	return (false);
}
