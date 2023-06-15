/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:00:54 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/13 12:00:57 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (str[0] != ' ' && str[ft_strlen(str) - 1] != ' ')
		return (str);
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
