/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:41:51 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/07 14:42:42 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*************************/
/* Delete horizontal tab */
/*************************/

char	*ft_one_space(char *str)
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
		i++;
	}
	ft_free_tab(tab);
	free(str);
	return (new_str);
}

char	*ft_delete_horizontal_tab(char *str)
{
	int		i;
	char	*new_str;

	new_str = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!new_str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			new_str[i] = ' ';
		else
			new_str[i] = str[i];
		i++;
	}
	new_str[i] = 0;
	new_str = ft_order_with_space(new_str);
	// new_str = ft_one_space(new_str);
	free(str);
	return (new_str);
}
