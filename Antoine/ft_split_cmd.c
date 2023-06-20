/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:12:51 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/13 12:12:53 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_check_redirec(char *str, char c)
{
	t_quotes	quote;

	ft_get_value_quote(&quote);
	while (str[quote.i] != 0)
	{
		ft_check_quotes(&quote, str, quote.i);
		if (quote.open_s == 0 && quote.open_d == 0)
		{
			if (str[quote.i] == c)
				return (true);
		}
		quote.i++;
	}
	return (false);
}

char	*ft_add_string(char *s1, char *s2)
{
	char	*tmp;

	tmp = s1;
	s1 = ft_strjoin(s1, s2);
	free(tmp);
	return (s1);
}

char	*ft_rewritten_str(char **tab)
{
	char	*str;
	int		i;

	i = 0;
	while (tab[i] != 0)
	{
		if (ft_check_redirec(tab[i], '>') == true
			|| ft_check_redirec(tab[i], '<') == true)
			tab[i] = ft_redirec(tab[i]);
		tab[i] = ft_delete_space(tab[i]);
		if (i == 0)
			str = ft_copy_str(tab[i]);
		else
		{
			str = ft_add_string(str, " | ");
			str = ft_add_string(str, tab[i]);
		}
		free(tab[i]);
		i++;
	}
	free(tab);
	return (str);
}

bool	ft_one_arg(char c)
{
	if (c == '\n'
		|| c == ' '
		|| c == '\t'
		|| c == ':'
		|| c == '!')
		return (true);
	else if (c == '$')
	{
		printf("%c\n", c);
		return (true);
	}
	else if (c == '/')
	{
		ft_error(DIRECTORY, "/", NULL);
		return (true);
	}
	return (false);
}

char	*ft_split_cmd(char *str)
{
	char	**tab;
	char	*tmp;

	if (ft_strlen(str) == 1)
	{
		if (ft_one_arg(str[0]) == false)
			ft_error(NOT_FOUND, str, NULL);
		free (str);
		return (0);
	}
	else if (ft_check_redirec(str, '|') == true)
	{
		tab = ft_split_mn(str, '|');
		tmp = str;
		str = ft_rewritten_str(tab);
		free(tmp);
	}
	else if (ft_check_redirec(str, '>') == true
		|| ft_check_redirec(str, '<') == true)
		str = ft_redirec(str);
	str = ft_delete_space(str);
	ft_parsing(str);
	return (str);
}
