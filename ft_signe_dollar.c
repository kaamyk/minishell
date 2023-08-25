/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signe_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:36:38 by xuluu             #+#    #+#             */
/*   Updated: 2023/08/25 11:33:04 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Find in "$USER '$USER'"
*/
int	ft_find_dollar_in_quotes(t_data *data, char *str)
{
	int		i;
	int		nb_signe;

	data->str_quotes = NULL;
	nb_signe = 0;
	i = 0;
	while (str[i] && nb_signe < 2)
	{
		if (str[i] == '"')
		{
			nb_signe++;
			ft_add_dollar(data, ft_character_to_string(str[i]), false);
		}
		else if (str[i] == '$')
			i += ft_found_dollar(data, &str[i]);
		else
			ft_add_dollar(data, ft_character_to_string(str[i]), false);
		i++;
	}
	ft_add_dollar(data, data->str_quotes, true);
	if (i > 0 && str[i - 1] == '"')
		i--;
	return (i);
}

/*
Find $USER
*/
int	ft_find_dollar_out_quotes(t_data *data, char *str, int i)
{
	data->str_quotes = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (i > 0)
				i--;
			break ;
		}
		else if (str[i] == '~')
			i = ft_check_signe_wave(data, str, i);
		else if (str[i] == '$')
			i += ft_found_dollar(data, &str[i]);
		else
			ft_add_dollar(data, ft_character_to_string(str[i]), false);
		i++;
	}
	if (str[i] == 0)
		i--;
	ft_add_dollar(data, data->str_quotes, true);
	return (i);
}

void	ft_add_str_dollar(t_data *data, int i)
{
	free(data->tab_cmd[i]);
	if (data->str_dollar)
		data->tab_cmd[i] = ft_copy_str(data->str_dollar);
	else
		data->tab_cmd[i] = NULL;
	free (data->str_dollar);
}

void	ft_signe_dollar(t_data *data, int i)
{
	int	m;

	if (ft_find_c(data->tab_cmd[i], '$') == true
		|| ft_find_c(data->tab_cmd[i], '~') == true)
	{
		data->str_dollar = NULL;
		m = 0;
		while (data->tab_cmd[i][m])
		{
			if (data->tab_cmd[i][m] == '"')
				m += ft_find_dollar_in_quotes(data, &data->tab_cmd[i][m]);
			else if (data->tab_cmd[i][m] == '\'')
				m += ft_ignore(data, &data->tab_cmd[i][m]);
			else
				m += ft_find_dollar_out_quotes(data, &data->tab_cmd[i][m], 0);
			if (data->tab_cmd[i][m] == 0)
				break ;
			m++;
		}
		ft_add_str_dollar(data, i);
	}
}
