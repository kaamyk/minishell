/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_output.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 18:27:32 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/17 18:28:07 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/************************/
/* Redirections [<] [<<]*/
/************************/

void	ft_put_value_in_data_output(t_data *data, char *line)
{
	if (!data->output)
		data->output = ft_copy_str(line);
	else
	{
		data->output = ft_add_string(data->output, "\n");
		data->output = ft_add_string(data->output, line);
	}
}

bool	ft_redirection_output(t_data *data, char *str)
{
	char	*limiter;
	char	*line;

	if (str[0] == '<')
	{
		data->s_heredoc = true;
		data->file = str;
		limiter = ft_find_str(data->file);
		if (str[1] == '<')
			line = ft_redirection3(limiter);
		else
			line = ft_redirection2(limiter);
		if (line)
			ft_put_value_in_data_output(data, line);
		free(limiter);
		free(line);
		return (1);
	}
	return (0);
}
