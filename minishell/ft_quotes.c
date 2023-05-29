/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:12:34 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/25 13:13:29 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_check_not_close(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '(')
			return (0);
		else if (str[i] == ')')
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_not_close2(char *str, char c)
{
	int		open;
	int		close;
	int		i;

	open = 0;
	close = 0;
	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == c)
			open++;
		else if (str[i] == ')')
			close++;
		i++;
	}
	if (open != close)
		return (1);
	return (0);
}

int	ft_check_not_close3(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '\'' || str[i] == '"')
			count++;
		i++;
	}
	if (count % 2 == 1)
		return (1);
	return (0);
}

char	*ft_get_quotes(char *str)
{
	if (ft_check_not_close(str) == 1)
		return (0);
	else if (ft_strchr(str, '(') != 0)
	{
		if (ft_check_not_close2(str, '(') == 1)
			str = ft_quotes(str, ')');
	}
	else if (ft_strchr(str, '\'') != 0)
	{
		if (ft_check_not_close3(str) == 1)
			str = ft_quotes(str, '\'');
	}
	else if (ft_strchr(str, '"') != 0)
	{
		if (ft_check_not_close3(str) == 1)
			str = ft_quotes(str, '"');
	}	
	return (str);
}
