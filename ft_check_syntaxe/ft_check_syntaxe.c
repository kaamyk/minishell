/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:15:47 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/25 17:11:56 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_check_len(t_data *data)
{
	size_t	len;

	len = ft_strlen(data->str);
	if (len == 0)
		return (1);
	return (0);
}

bool	ft_check_space_string(t_data *data)
{
	int		i;
	size_t	space;

	space = 0;
	i = 0;
	while (data->str[i])
	{
		if (data->str[i] == ' ' || data->str[i] == '\t')
			space++;
		i++;
	}
	if (space == ft_strlen(data->str))
		return (1);
	return (0);
}

bool	ft_check_first_last_cmd(t_data *data)
{
	int	i;

	i = ft_strlen(data->str) - 1;
	if (data->str[0] == '|' || data->str[0] == '&')
	{
		ft_error(SYNTAXE, &data->str[0], 0);
		data->exit_code = 2;
		return (true);
	}
	if (data->str[i] == '|' || data->str[i] == '&'
		|| data->str[i] == '>' || data->str[i] == '<')
	{
		ft_error(SYNTAXE, &data->str[i], 0);
		data->exit_code = 2;
		return (true);
	}
	return (false);
}

bool	ft_check_syntaxe(t_data *data)
{
	if (ft_check_len(data) == true)
		return (1);
	if (ft_check_space_string(data) == true)
		return (1);
	data->str = ft_delete_space(data->str);
	if (ft_check_open_quotes(data) == true)
		return (1);
	if (ft_check_first_last_cmd(data) == true)
		return (1);
	return (0);
}
