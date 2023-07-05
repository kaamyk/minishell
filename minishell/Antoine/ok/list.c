/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/15 16:00:01 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env;

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
			free_list(n_l, i);
			return (NULL);
		}
		++i;
	}
	return (n_l);
}

bool	cpy_list(char **dest, char **src, size_t l_src)
{
	size_t	i;

	i = 0;
	while (i < l_src)
	{
		if (src[i] == NULL)
		{
			dest[i++] = NULL;
			continue ;
		}
		dest[i] = ft_strdup(src[i]);
		if (dest[i] == NULL)
		{
			free_list(dest, i);
			return (1);
		}
		++i;
	}
	return (0);
}

char	**join_list(char **lst1, char **lst2, size_t len_l1, size_t len_l2)
{
	char	**res;
	size_t	len;

	if (lst1 == NULL || lst2 == NULL)
		return (NULL);
	len = len_l1 + len_l2 + 1;
	res = ft_calloc (len, sizeof(char *));
	if (res == NULL)
		return (NULL);
	if (cpy_list(res, lst1, len_l1) == 1)
		return (NULL);
	if (cpy_list(res + len_l1, lst2, len_l2))
		return (NULL);
	return (res);
}
