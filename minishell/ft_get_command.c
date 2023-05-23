/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:15:47 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/22 18:15:49 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Gere l'espace
*/
char	*ft_delete(char *str, int len)
{
	int	i;
	int	n;
	char	*line;

	line = (char *)malloc((len + 1) * sizeof(char));
	if (!line)
		return (0);
	i = 0;
	while (str[i] != 0 && str[i] == ' ')
		i++;
	n = 0;
	while (str[i] != 0 && n < len)
	{
		line[n] = str[i];
		n++;
		i++;
	}
	line[n] = 0;
	free(str);
	//printf("%s %ld\n", line, ft_strlen(line));
	return (line);
}

char	*ft_delete_espace(char *str)
{
	int		start;
	int		end;

	start = 0;
	while (str[start] != 0 && str[start] == ' ')
		start++;
	end = ft_strlen(str);
	if (str[end - 1] == ' ')
	{
		while (end > 0 && str[end - 1] == ' ')
			end--;
	}
	return (ft_delete(str, end - start));
}

char	*ft_quotes(char *line, char c)
{
	char	*tmp;
	char	*str;

	while (1)
	{
		tmp = line;
		str = get_line(">");
		line = ft_strjoin(line, str);
		free(tmp);
		if (ft_strchr(str, c) != 0)
			break ;
	}
	return (line);
}

void	ft_get_command(char *line)
{
	char	*command;
	int		i;

	/*quotes () "" '' */
	if (ft_strchr(line, '(') != 0)
		line = ft_quotes(line, ')');
	else if (ft_strchr(line, '\'') != 0)
		line = ft_quotes(line, '\'');
	else if (ft_strchr(line, '"') != 0)
		line = ft_quotes(line, '"');

	if (line[0] == '/') /*check a chemin*/
	{
		ft_check_dir(line, 2);
		return ;
	}
	else if (ft_strlen(line) == 1)
	{
		ft_determine_command(line);
		return ;
	}

	if (ft_strchr(line, ' ') == 0)
	{
		ft_determine_command(line);
		free(line);
		return ;
	}
	else
		line = ft_delete_espace(line);

	/*echo salut*/
	i = 0;
	while (line[i] != 0 && line[i] != ' ')
		i++;
	command = (char *)malloc((i + 1) * sizeof(char));
	if (!command)
		return ;
	i = 0;
	while (line[i] != 0 && line[i] != ' ')
	{
		command[i] = line[i];
		i++;
	}
	command[i] = 0;
	ft_determine_command(command);
	free(command);
	free(line);
}

void	ft_get_command2(char *str, char c)
{
	int		i;
	char	**line;

	line = ft_split(str, c);
	i = 0;
	while (line[i] != 0)
	{
		line[i] = ft_delete_espace(line[i]);
		ft_get_command(line[i]);
		i++;
	}
	free(line);
}
