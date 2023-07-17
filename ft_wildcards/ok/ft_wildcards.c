/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:47:13 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/17 12:47:16 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_env	*g_env;

bool	ft_find(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (s2[i] == 0)
		return (1);
	return (0);
}

char	*ft_determine_the_path(t_data *data, char *str)
{
	int		len;
	char	*list_fd;

	list_fd = ft_get_current_file_directory(data, ".");
	len = ft_strlen(str);
	if (len > 1)
	{
		if (str[0] == '*' && str[len - 1] == '*')
		{
			printf("* C *\n");
			list_fd = ft_find_center(str, list_fd);
		}
		else if (str[0] != '*' && str[len - 1] == '*')
		{
			printf("F *\n");
			list_fd = ft_find_first(str, list_fd);
		}
		else if (str[0] == '*' && str[len - 1] != '*')
		{
			printf("* E\n");
			list_fd = ft_find_end(str, list_fd);
		}
		else
		{
			printf("F * C * E\n");
			list_fd = ft_wildcards_is_center(str, list_fd);
		}
	}
	if (list_fd)
	{
		free(str);
		return (list_fd);
	}
	return (str);
}

void	ft_wildcards(t_data *data, char *str)
{
	int		i;
	char	**tab;

	if (ft_find_c(str, '*') == true && ft_find_c(str, ' ') == true)
	{
		tab = ft_split(str, ' ');
		data->tab_wildcards = tab;
		i = 0;
		while (tab[i])
		{
			tab[i] = ft_delete_space(tab[i]);
			if (ft_find_c(tab[i], '*') == true)
			{
				tab[i] = ft_one_wildcard(tab[i]);
				tab[i] = ft_determine_the_path(data, tab[i]);
				printf("new_list = [%s]\n", tab[i]);
			}
			i++;
		}
		ft_free_tab(tab);
	}
}
