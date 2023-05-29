/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:15:47 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/26 11:11:59 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_arg(char *line, size_t command_len)
{
	char	*arg;
	size_t	i;
	size_t	j;

	i = 0;
	arg = NULL;
	while (line[i] && line[i] == ' ')
		++i;
	i += command_len;
	while (line[i] && line[i] == ' ')
		++i;
	if (ft_strlen(line) - i > 0)
		arg = malloc (sizeof(char) * (ft_strlen(line) - i + 1));
	else
		return (NULL);
	j = 0;
	while (line[i])
	{
		arg[j] = line[i];
		++j;
		++i;
	}
	arg[j] = 0;
	return (arg);
}

char	*ft_split_quotes(char *line)
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

char	*ft_get_command(char *line)
{
	char	*command;
	size_t	i;
	size_t	j;
	size_t	len;

	len = 0;
	i = 0;
	while (line[i] != 0 && line[i] == ' ')
		++i;
	if (ft_strchr(line, '"') == 0 && ft_strchr(line, '\'') == 0)
		while (line[i + len] != 0 && line[i + len] != ' ')
			++len;
	else
		return (ft_split_quotes(line + i));
	command = NULL;
	if (len != 0)
		command = malloc(sizeof(char) * (len + 1));
	if (command == NULL)
		return (NULL);
	command[len] = 0;
	j = 0;
	while (line[j + i] != 0 && line[j + i] != ' ')
	{
		command[j] = line[j + i];
		++j;
	}
	return (command);
}

void	ft_split_line(char *line)
{
	char	*command;
	char	*arg;

	command = NULL;
	arg = NULL;
	if (ft_quotes(line) != 0)
	{
		printf("Unexpected EOF : '%s' has open quotes\n", line);
		return ;
	}
	if (ft_strlen(line) == 1)
	{
		if (ft_one_arg(line[0]) == 0)
			ft_error(NOT_FOUND, line, NULL);
		return ;
	}
	command = ft_get_command(line);
	if (command == NULL)
		return ;
	arg = ft_get_arg(line, ft_strlen(command));
	ft_determine_command(command, arg);
	free(command);
	free(arg);
}
