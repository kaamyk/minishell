/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signe_dollar2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:36:18 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/28 16:36:31 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_dollar(t_data *data, char *str, bool big)
{
	if (str)
	{
		if (big == true)
		{
			if (!data->str_dollar)
				data->str_dollar = ft_copy_str(str);
			else
				data->str_dollar = ft_add_string(data->str_dollar, str);
		}
		else
		{
			if (!data->str_quotes)
				data->str_quotes = ft_copy_str(str);
			else
				data->str_quotes = ft_add_string(data->str_quotes, str);
		}
	}
	free(str);
}

char	*ft_character_to_string(char character)
{
	char	*string;

	string = (char *)malloc(2 * sizeof(char));
	if (!string)
		return (0);
	string[0] = character;
	string[1] = 0;
	return (string);
}

void	ft_change_value(t_data *data, char *str, int len)
{
	int		i;
	char	*new_str;
	char	*tmp;

	if (len == 1)
		new_str = ft_character_to_string('$');
	else if (len == 2 && str[1] == '?')
		new_str = ft_itoa(data->exit_code);
	else
	{
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
		tmp = new_str;
		new_str = ft_get_value(data->env, new_str);
		free(tmp);
	}
	ft_add_dollar(data, new_str, false);
}

/*
str_change = $USER
*/
int	ft_found_dollar(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i > 0 && str[i] == '$')
		{
			i--;
			break ;
		}
		else if (str[i] == ' ' || str[i] == '\t'
			|| str[i] == '\'' || str[i] == '"')
		{
			i--;
			break ;
		}
		i++;
	}
	if (str[i] == 0)
		i--;
	ft_change_value(data, str, i + 1);
	return (i);
}
