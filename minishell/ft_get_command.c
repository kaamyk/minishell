/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:15:47 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/26 11:22:05 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Gere l'espace
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
	return (line);
}

char	*ft_delete_space(char *str)
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

int	ft_one_arg(char c)
{
	printf("ici\n");
	if (c == '\n'
		|| c == ' '
		|| c == '	'
		|| c == ':'
		|| c == '!')
		return (1);
	return (0);
}

void	ft_get_command2(char *str, char c)
{
	int		i;
	char	**line;

	line = ft_split(str, c);
	i = 0;
	while (line[i] != 0)
	{
		if (ft_quotes(line[i]) != 0)
		{
			printf("Unexpected EOF : '%s' has open quotes\n", line[i]);
			return ;
		}
		line[i] = ft_delete_space(line[i]);
		// if (c == '>')
		// 	ft_redirections(line[i]);
		// else
		ft_split_line(line[i]);
		i++;
	}
	free(line);
}
