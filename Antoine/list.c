/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/01 17:56:38 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(char **l)
{
	size_t	i;

	i = 0;
	while (l[i])
	{
		printf("%s\n", l[i]);
		++i;
	}
}

size_t	len_list(char **l)
{
	size_t	len;

	len = 0;
	while (l[len])
		++len;
	return (len);
}

char	**dup_list(char **l)
{
	char	**n_l;
	size_t	len;
	size_t	i;

	len = len_list(l);
	n_l = malloc(sizeof(char *) * (len + 1));
	n_l[len] = NULL;
	if (n_l == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		n_l[i] = ft_strdup(l[i]);
		if (n_l[i] == NULL)
		{
			free_list((void **)n_l);
			return (NULL);
		}
		++i;
	}
	return (n_l);
}

bool	cpy_list(char **l_dest, char **l_src)
{
	size_t	len_src;
	size_t	i;

	len_src = len_list(l_src);
	i = 0;
	while (l_src[i] && i < len_src)
	{
		l_dest[i] = ft_strdup(l_src[i]);
		if (l_dest[i] == NULL)
		{
			free_list((void **)l_dest);
			return (1);
		}
		++i;
	}
	return (0);
}

char	**join_list(char **lst1, char **lst2)
{
	char	**res;
	size_t	len;

	len = len_list(lst1) + len_list(lst2) + 1;
	res = ft_calloc (len, sizeof(char *));
	if (res == NULL)
		return (NULL);
	if (cpy_list(res, lst1) == 1)
		return (NULL);
	if (cpy_list(res + len_list(res), lst2))
		return (NULL);
	return (res);
}
