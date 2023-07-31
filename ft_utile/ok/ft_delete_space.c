/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:00:54 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/13 12:00:57 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_delete_space(char *str)
{
	int		i;
	char	**tab;
	char	*new_str;

	tab = ft_split(str, ' ');
	i = 0;
	while (tab[i])
	{
		if (i == 0)
			new_str = ft_copy_str(tab[i]);
		else
		{
			new_str = ft_add_string(new_str, " ");
			new_str = ft_add_string(new_str, tab[i]);
		}
		free(tab[i]);
		i++;
	}
	free(tab);
	free(str);
	return (new_str);
}
