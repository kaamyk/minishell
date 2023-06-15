/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_<<.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:19:02 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/13 19:20:14 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_redirection42(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	if (s1[i] == 0 && s2[i] == 0)
		return (true);
	else
		return (false);
}

void	ft_redirection4(char *str)
{
	char	*line;
	bool	find;
	char	*string;
	int		time;

	ft_signal();
	find = false;
	time = 0;
	while (1)
	{
		if (find == true)
			break ;
		line = get_line("> ");
		if (!line)
			break ;
		if (ft_redirection42(str, line) == true)
		{
			printf("%s - %s\n", str, line);
			find = true;
		}
		else
		{
			if (time == 0)
				string = ft_copy_str(line);
			else
			{
				string = ft_add_string(string, " ");
				string = ft_add_string(string, line);
			}
		}
		free(line);
		time++;
	}
	printf("[%s]\n", string);
	free(string);
}
