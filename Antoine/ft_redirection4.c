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

bool	ft_compare_str(char *s1, char *s2)
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

char	*ft_creer_big_string(int time, char *string, char *line)
{
	if (time == 0)
		string = ft_copy_str(line);
	else
	{
		if (string[ft_strlen(string) - 1] != '\n')
			string = ft_add_string(string, "\n");
		string = ft_add_string(string, line);
	}
	return (string);
}

void	ft_redirection4(t_data *data, char *str)
{
	char	*line;
	bool	find;
	char	*string;
	int		time;

	ft_signal();
	find = false;
	time = 0;
	string = NULL;
	while (1)
	{
		if (find == true)
			break ;
		line = get_line("> ");
		if (!line)
			break ;
		if (ft_compare_str(str, line) == true)
			find = true;
		else
			string = ft_creer_big_string(time, string, line);
		free(line);
		time++;
	}
	data->result = string;
}
