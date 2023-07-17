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
check <>, ><
*/
bool	ft_check_redirection(char *str, int i)
{
	int		f;

	f = i;
	while (i >= 0)
	{
		if (i < f)
		{
			if ((str[f] == '>' && str[i] == '<')
				|| (str[f] == '<' && str[i] == '>'))
				return (1);
			else if (str[i] != ' ')
				break ;
		}
		i--;
	}
	return (0);
}

/*
check &|, |&, <|, >|, <&, >&
*/
bool	ft_check_position_of_signe(char *str, int i)
{
	int	f;

	f = i;
	while (i >= 0)
	{
		if (i < f)
		{
			if (str[f] == '|' || str[f] == '&')
			{
				if (str[i] == '>' || str[i] == '<'
					|| str[i] == '|' || str[i] == '&')
					return (1);
				else if (str[i] != ' ')
					break ;
			}
		}
		i--;
	}
	return (0);
}

/*
check >>>, >> >, &&&, || |
*/
bool	ft_check_double(char *str, int i)
{
	int	f;

	f = i;
	while (i >= 0)
	{
		if (i < f)
		{
			if (str[i] == str[f])
				return (1);
			else if (str[i] != ' ')
				break ;
		}
		i--;
	}
	return (0);
}

bool	ft_check_syntax_inside2(t_data *data, char *str, int i)
{
	int		position;

	position = i;
	if (str[i - 1] == str[i])
		position = i - 1;
	if (ft_check_double(str, position) == true
		|| ft_check_redirection(str, position) == true
		|| ft_check_position_of_signe(str, position) == true)
	{
		ft_error(SYNTAXE, &str[i], 0);
		data->exit_code = 2;
		return (1);
	}
	return (0);
}

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
