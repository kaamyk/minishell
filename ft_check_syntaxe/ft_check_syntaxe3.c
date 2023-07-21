/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntaxe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:21:51 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/01 15:21:53 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
check ; or \
*/
bool	ft_check_special_characters(t_data *data, char character)
{
	if (character == ';' || character == '\\')
	{
		ft_error(SYNTAXE, &character, 0);
		data->exit_code = 2;
		return (1);
	}
	return (0);
}

bool	ft_check_syntax_inside(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_check_special_characters(data, str[i]) == true)
			return (1);
		if (i > 0)
		{
			if (str[i] == '|' || str[i] == '&'
				|| str[i] == '>' || str[i] == '<')
			{
				if (ft_check_syntax_inside2(data, str, i) == true)
					return (1);
			}
			else if (i > 1 && str[i - 1] == '&' && str[i - 2] != '&')
			{
				ft_error(SYNTAXE, &str[i - 1], 0);
				data->exit_code = 2;
				return (1);
			}
		}
		i++;
	}
	return (0);
}
