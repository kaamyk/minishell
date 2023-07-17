/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_center.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:47:53 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/17 12:47:56 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**************************/
/* [* Center * Center2 *] */
/**************************/

bool	ft_read_each_character(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == s2[0])
		{
			if (ft_find(&s1[i], s2) == true)
				return (true);
		}
		i++;
	}
	return (false);
}

char	*ft_find_center_in_list2(char *str, char *str_find, char *new_list)
{
	if (ft_read_each_character(str, str_find) == true)
	{
		if (!new_list)
			new_list = ft_copy_str(str);
		else
		{
			new_list = ft_add_string(new_list, "\n");
			new_list = ft_add_string(new_list, str);
		}
	}
	return (new_list);
}

char	*ft_find_center_in_list(char *str, char *list_fd)
{
	int		i;
	int		len;
	int		len_line;
	char	**tab;
	char	*new_list;

	tab = ft_split(list_fd, '\n');
	len = ft_strlen(str);
	new_list = NULL;
	i = 0;
	while (tab[i])
	{
		tab[i] = ft_delete_space(tab[i]);
		len_line = ft_strlen(tab[i]);
		if (len_line >= len)
			new_list = ft_find_center_in_list2(tab[i], str, new_list);
		i++;
	}
	ft_free_tab(tab);
	free(list_fd);
	return (new_list);
}

char	*ft_find_center(char *str, char *list_fd)
{
	int		i;
	char	*new_list;
	char	**tab;

	new_list = ft_copy_str(list_fd);
	tab = ft_split(str, '*');
	i = 0;
	while (tab[i])
	{
		tab[i] = ft_delete_space(tab[i]);
		new_list = ft_find_center_in_list(tab[i], new_list);
		if (!new_list)
			break ;
		i++;
	}
	ft_free_tab(tab);
	free(list_fd);
	return (new_list);
}
