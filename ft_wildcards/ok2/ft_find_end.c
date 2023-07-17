/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:48:43 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/17 12:48:46 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/********************/
/* [* Center * End] */
/********************/

char	*ft_find_end_in_list2(char *str, char *str_find, char *new_list)
{
	int	len_str;
	int	len_str_find;

	len_str = ft_strlen(str);
	len_str_find = ft_strlen(str_find);
	if (ft_find(&str[len_str - len_str_find], str_find) == true)
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

char	*ft_find_end_in_list(char *str, char *list_fd)
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
			new_list = ft_find_end_in_list2(tab[i], str, new_list);
		i++;
	}
	ft_free_tab(tab);
	free(list_fd);
	return (new_list);
}

char	*ft_find_end(char *str, char *list_fd)
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
		if (tab[i + 1] == 0)
			new_list = ft_find_end_in_list(tab[i], new_list);
		else
			new_list = ft_find_center_in_list(tab[i], new_list);
		if (!new_list)
			break ;
		i++;
	}
	ft_free_tab(tab);
	free(list_fd);
	return (new_list);
}
