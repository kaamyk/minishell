/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:24:28 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/07 17:25:24 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/****************************************/
/* Put the redirection < or << at first */
/****************************************/

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	*ft_find_not_out(char **tab, int *tab_position, int m, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		tab[i] = ft_delete_space(tab[i]);
		if (tab[i][0] != '<')
		{
			tab_position[m] = i;
			m++;
		}
		i++;
	}
	return (tab_position);
}

int	*ft_find_re_out(char **tab, int len)
{
	int	i;
	int	m;
	int	*tab_position;

	tab_position = (int *)malloc(len * sizeof(int));
	if (!tab_position)
		return (0);
	m = 0;
	i = 0;
	while (i < len)
	{
		tab[i] = ft_delete_space(tab[i]);
		if (tab[i][0] == '<')
		{
			tab_position[m] = i;
			m++;
		}
		i++;
	}
	tab_position = ft_find_not_out(tab, tab_position, m, len);
	return (tab_position);
}

char	*ft_check_order(char **tab)
{
	int		i;
	int		len;
	int		*tab_position;
	int		p;
	char	*new_str;

	len = ft_tablen(tab);
	tab_position = ft_find_re_out(tab, len);
	i = 0;
	while (i < len)
	{
		p = tab_position[i];
		if (i == 0)
			new_str = ft_copy_str(tab[p]);
		else
		{
			new_str = ft_add_string(new_str, " ; ");
			new_str = ft_add_string(new_str, tab[p]);
		}
		free(tab[p]);
		i++;
	}
	free(tab);
	free(tab_position);
	return (new_str);
}

/*
[wc -l < file] --> [< file wc -l]
*/
char	*ft_put_reout_at_first(t_data *data, char *str)
{
	char	**tab;
	char	*new_str;

	new_str = ft_add_semicolon(str);
	tab = ft_create_tab_re(data, new_str);
	free(new_str);
	new_str = ft_check_order(tab);
	free(str);
	return (new_str);
}
