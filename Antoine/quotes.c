/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:15:47 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/01 11:44:01 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*del_quotes(char *line)
{
	char	*command;
	size_t	i;
	size_t	j;
	size_t	len;

	len = 0;
	while (line[len + 1] && line[len + 1] != '"')
		++len;
	while (line[len + 2] && line[len + 2] != ' ')
		++len;
	command = NULL;
	if (len != 0)
		command = malloc(sizeof(char) * (len + 1));
	if (command == NULL)
		return (NULL);
	command[len] = 0;
	j = 0;
	i = 1;
	while (j < len && line[i] != 0)
	{
		if (line[i] != '"' && line[i] != '\'')
		{
			command[j] = line[i];
			++j;
		}
		++i;
	}
	return (command);
}

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
				printf(">>> OPEN QUOTES <<<\n");
				return (true);
			}
		}
		++i;
	}
	printf(">>> QUOTES ARE CLOSED <<<\n");
	return (false);
}

bool	ft_quotes(char *line)
{
	if (ft_check_open_quotes(line) == true)
		return (true);
	return (false);
}
