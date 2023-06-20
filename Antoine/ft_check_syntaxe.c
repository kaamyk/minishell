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

#include "minishell.h"

bool	ft_check_syntaxe_direction(char *str)
{
	char	*arg;
	int		i;
	bool	error;

	error = false;
	i = 1;
	if ((str[0] == '>' && str[1] == '>') || (str[0] == '<' && str[1] == '<'))
		i++;
	arg = ft_copy_str(&str[i]);
	if (arg[0] == '>' || arg[0] == '<')
		error = true;
	free(arg);
	return (error);
}

bool	ft_check_first_last_cmd(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	if (str[0] == '|')
	{
		ft_error(SYNTAXE, &str[0], 0);
		return (true);
	}
	if (str[i] == '|' || str[i] == '>' || str[i] == '<')
	{
		ft_error(SYNTAXE, &str[i], 0);
		return (true);
	}
	return (false);
}

bool	ft_check_doule(char *str, int i)
{
	while (i > 0)
	{
		if (str[i] == '|')
			return (true);
		else if (str[i] != ' ' && str[i] != '\t')
			break ;
		i--;
	}
	return (false);
}

bool	ft_check_syntaxe2(char *str, int i)
{
	if (str[i] == ';' || str[i] == '\\')
	{
		ft_error(SYNTAXE, &str[i], 0);
		return (true);
	}
	if (str[i] == '|')
	{
		if (ft_check_doule(str, i - 1) == true)
		{
			ft_error(SYNTAXE, &str[i], 0);
			return (true);
		}
	}
	if (str[i] == '>' || str[i] == '<')
	{
		if (ft_check_syntaxe_direction(&str[i]) == true)
		{
			ft_error(SYNTAXE, &str[i], 0);
			return (true);
		}
	}
	return (false);
}

bool	ft_check_syntaxe(char *str)
{
	t_quotes	quote;

	if (ft_check_first_last_cmd(str) == true)
		return (true);
	ft_get_value_quote(&quote);
	while (str[quote.i] != 0)
	{
		ft_check_quotes(&quote, str, quote.i);
		if (quote.open_s == 0 && quote.open_d == 0)
		{
			if (ft_check_syntaxe2(str, quote.i) == true)
				return (true);
		}
		quote.i++;
	}
	return (false);
}
