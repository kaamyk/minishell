/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards_is_center.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:48:59 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/17 12:49:02 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**************************/
/* [First * Center * End] */
/**************************/

char	*ft_wildcards_is_center(char *str, char *list_fd)
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
		if (i == 0)
			new_list = ft_find_first_in_list(tab[i], new_list);
		else if (tab[i + 1] == 0)
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
