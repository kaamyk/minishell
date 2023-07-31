/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signe_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:36:38 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/28 16:36:40 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
str_copy = '$USER "$USER"'
*/
void	ft_ignore2(t_data *data, char *str, int len)
{
	int		i;
	char	*new_str;

	new_str = (char *)malloc((len + 1) * sizeof(char));
	if (!new_str)
		return ;
	i = 0;
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = 0;
	ft_add_dollar(data, new_str, true);
}

int	ft_ignore(t_data *data, char *str)
{
	int		i;
	int		nb_signe;

	nb_signe = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			nb_signe++;
		if (nb_signe == 2)
			break ;
		i++;
	}
	ft_ignore2(data, str, i + 1);
	return (i);
}

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
	return (i);
}

/*
Find $USER
*/
int	ft_find_dollar_out_quotes(t_data *data, char *str)
{
	int		i;

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

void	ft_signe_dollar(t_data *data, int i)
{
	int	m;

	if (ft_find_c(data->tab_cmd[i], '$') == true)
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
				m += ft_find_dollar_out_quotes(data, &data->tab_cmd[i][m]);
			if (data->tab_cmd[i][m] == 0)
				break ;
			m++;
		}
		free(data->tab_cmd[i]);
		if (data->str_dollar)
			data->tab_cmd[i] = ft_copy_str(data->str_dollar);
		else
			data->tab_cmd[i] = NULL;
		free (data->str_dollar);
	}
}
