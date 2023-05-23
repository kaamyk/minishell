/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:15:47 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/23 15:26:23 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_command(char *line)
{
	char	*command;
	int		i;

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
}

/*
Les commandes avec ; ou |
*/
char	*ft_delete(char *str, int len)
{
	int		i;
	int		n;
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
	//printf("%d %d %d\n", start, end, end - start);
	return (ft_delete(str, end - start));
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
		//printf("%s %ld\n", line[i], ft_strlen(line[i]));
		ft_get_command(line[i]);
		free(line[i]);
		i++;
	}
	free(line);
}
