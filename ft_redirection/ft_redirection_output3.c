/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_output3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:19:02 by xuluu             #+#    #+#             */
/*   Updated: 2023/08/31 19:06:33 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern bool	g_run;

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
	char	*string;

	string = NULL;
	g_run = true;
	while (g_run == true)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_compare_str(str, line) == true)
		{
			free(line);
			break ;
		}
		else if (ft_strlen(line) > 0)
			string = ft_creer_big_string(string, line);
		free(line);
	}
	if (g_run == false)
		data->exit_code = 130;
	g_run = true;
	return (string);
}
