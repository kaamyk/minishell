/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_output3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:19:02 by xuluu             #+#    #+#             */
/*   Updated: 2023/08/25 13:29:24 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/************************************/
/* Get input of the redirection << */
/************************************/

char	*ft_creer_big_string(char *string, char *line)
{
	if (!string)
		string = ft_copy_str(line);
	else
	{
		if (string[ft_strlen(string) - 1] != '\n')
			string = ft_add_string(string, "\n");
		string = ft_add_string(string, line);
	}
	return (string);
}

char	*ft_redirection3(t_data *data, char *str)
{
	char	*line;
	bool	find;
	char	*string;

	ft_signal(data);
	find = false;
	string = NULL;
	while (1)
	{
		if (find == true)
			break ;
		line = take_input("> ");
		if (!line)
			break ;
		if (ft_compare_str(str, line) == true)
			find = true;
		else if (ft_strlen(line) > 0)
			string = ft_creer_big_string(string, line);
		free(line);
	}
	return (string);
}
