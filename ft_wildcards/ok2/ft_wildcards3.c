/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:47:37 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/17 12:47:40 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/***********************/
/* Change **.c --> *.c */
/***********************/

char	*ft_one_wildcard3(char *str, char *new_str, int i, bool start_wildcard)
{
	if (i == 0)
	{
		if (start_wildcard == true)
		{
			new_str = ft_copy_str("*");
			new_str = ft_add_string(new_str, str);
		}
		else
			new_str = ft_copy_str(str);
	}
	else
	{
		new_str = ft_add_string(new_str, "*");
		new_str = ft_add_string(new_str, str);
	}
	return (new_str);
}

char	*ft_one_wildcard2(char *str, bool start_wildcard, bool end_wildcard)
{
	int		i;
	char	*new_str;
	char	**tab;

	tab = ft_split(str, '*');
	i = 0;
	while (tab[i])
	{
		if (tab[i])
		{
			tab[i] = ft_delete_space(tab[i]);
			new_str = ft_one_wildcard3(tab[i], new_str, i, start_wildcard);
			if (tab[i + 1] == 0 && end_wildcard == true)
				new_str = ft_add_string(new_str, "*");
		}
		i++;
	}
	ft_free_tab(tab);
	return (new_str);
}

bool	ft_check_string_wildcard(char *str)
{
	int	i;
	int	nb_wildcard;

	nb_wildcard = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			nb_wildcard++;
		i++;
	}
	if (nb_wildcard == i)
		return (1);
	return (0);
}

char	*ft_one_wildcard(char *str)
{
	char	*new_str;
	bool	start_wildcard;
	bool	end_wildcard;

	if (ft_check_string_wildcard(str) == true)
		new_str = ft_copy_str("*");
	else
	{
		start_wildcard = false;
		if (str[0] == '*')
			start_wildcard = true;
		end_wildcard = false;
		if (str[ft_strlen(str) - 1] == '*')
			end_wildcard = true;
		new_str = ft_one_wildcard2(str, start_wildcard, end_wildcard);
	}
	free(str);
	return (new_str);
}
