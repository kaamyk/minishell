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

#include "../minishell.h"

char	*ft_get_str_without_space(char *str)
{
	int		i;
	char	end;
	char	*new_str;

	new_str = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!new_str)
		return (0);
	end = str[0];
	i = 0;
	while (str[i])
	{
		if (end != '"' && end != '\''
			&& (str[i] == ' ' || str[i] == '"' || str[i] == '\''))
			break ;
		new_str[i] = str[i];
		i++;
		if ((end == '"' || end == '\'') && (str[i - 1] == end) && (i - 1 > 0))
		{
			break ;
		}
	}
	new_str[i] = 0;
	return (new_str);
}

char	*ft_delete_space2(char *str, int i, int m)
{
	char	*new_str;
	char	*find;

	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'' || str[i] != ' ')
		{
			find = ft_get_str_without_space(&str[i]);
			if (m == 0)
				new_str = ft_copy_str(find);
			else
				new_str = ft_add_string(new_str, find);
			i += ft_strlen(find);
			free(find);
			m++;
		}
		else
		{
			if (i > 0 && str[i - 1] != ' ' && m > 0)
				new_str = ft_add_string(new_str, " ");
			i++;
		}
	}
	free(str);
	return (new_str);
}

char	*ft_delete_space(char *str)
{
	char	*new_str;

	new_str = ft_delete_space2(str, 0, 0);
	return (new_str);
}
