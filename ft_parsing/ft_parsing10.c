/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing10.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:28:01 by xuluu             #+#    #+#             */
/*   Updated: 2023/09/01 11:47:48 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_check_empty_file(char *str)
{
	int	i;

	i = 1;
	if (str[i] == '>')
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\'' && str[i + 1] == '\'')
		return (1);
	if (str[i] == '"' && str[i + 1] == '"')
		return (1);
	return (0);
}

char	*ft_change_file_direc3(char *empty, char *file)
{
	int		i;
	char	*new_str;

	new_str = (char *)malloc((ft_strlen(empty) + 1) * sizeof(char));
	if (!new_str)
		return (0);
	i = 0;
	while (empty[i])
	{
		new_str[i] = empty[i];
		i++;
	}
	new_str[i] = 0;
	free(file);
	return (new_str);
}

char	*ft_change_file_direc2(char *empty, char *file)
{
	int		i;
	char	*new_str;

	new_str = (char *)malloc((ft_strlen(file) + 1) * sizeof(char));
	if (!new_str)
		return (0);
	i = 0;
	while (file[i])
	{
		new_str[i] = file[i];
		i++;
	}
	new_str[i] = 0;
	free(empty);
	return (new_str);
}

char	**ft_change_file_direc(char **tab)
{
	int		i;
	int		id_change;
	char	*swap;

	id_change = 1;
	i = 0;
	while (tab[i])
	{
		if (i > 0 && tab[i][0] == '>' && tab[i - 1][0] != '>')
			id_change = i;
		if (tab[i][0] == '>')
		{
			if (ft_check_empty_file(tab[i]) == 1
				&& ft_check_empty_file(tab[id_change]) == 0)
			{
				swap = ft_strdup(tab[i]);
				tab[i] = ft_change_file_direc2(tab[i], tab[id_change]);
				tab[id_change] = ft_change_file_direc3(swap, tab[id_change]);
				free(swap);
			}
		}
		i++;
	}
	return (tab);
}
