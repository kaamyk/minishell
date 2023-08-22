/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:53:45 by xuluu             #+#    #+#             */
/*   Updated: 2023/08/01 16:54:26 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_command(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i];
			i++;
			while (str[i] && str[i] != c)
				i++;
			if (!str[i] || !str[i + 1] || str[i + 1] == ' ')
				break ;
		}
		i++;
	}
	return (i);
}

void	ft_check_exit_code2(t_data *data, int i)
{
	char	*tmp;
	int		end;

	if (data->tab_cmd[i][0] == '|')
	{
		tmp = data->tab_cmd[i];
		data->tab_cmd[i] = ft_copy_str(&data->tab_cmd[i][2]);
		free(tmp);
	}
	end = ft_get_command(data->tab_cmd[i]);
	tmp = data->tab_cmd[i];
	data->tab_cmd[i] = ft_substr(data->tab_cmd[i], 0, end);
	free(tmp);
	data->tab_cmd[i] = ft_delete_quotes(data, data->tab_cmd[i]);
}

void	ft_check_exit_code(t_data *data, int i)
{
	if (data->tab_cmd[i] && data->exit_code != 0)
	{
		ft_check_exit_code2(data, i);
		if (data->exit_code == 126)
			ft_error(DIRECTORY, data->tab_cmd[i], 0);
		else if (data->exit_code == 127)
		{
			if (ft_strrchr(data->tab_cmd[i], '/') != 0)
				ft_error(NO_SUCH, data->tab_cmd[i], 0);
			else
				ft_error(NOT_FOUND, data->tab_cmd[i], 0);
		}
		else if (data->exit_code == 1 && data->tab_cmd[i][0] == '<')
			ft_error(NO_SUCH, &data->tab_cmd[i][2], 0);
	}
}
