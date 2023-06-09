/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/09 19:52:29 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env;

bool	key_is_valid(size_t *ranks, size_t len, size_t r_g)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (ranks[i] == r_g)
			return (1);
		++i;
	}
	return (0);
}

char	**delete_items_list(size_t *ranks, size_t len)
{
	t_env	n_env;
	size_t	i;
	size_t	j;

	n_env = malloc(sizeof(t_env));
	i = 0;
	while (g_env->key[i] != NULL)
	{
		if (key_is_valid(ranks, i) == 0)
		{
			n_env->key[j] = ft_strdup(g_env->key[i]);
			n_env->value[j] = ft_strdup(g_env->value[i]);
			++j;
		}
		++i;
	}
	free_env(g_env);
	g_env = n_env;
	return (NULL);
}

size_t	*find_ranks(t_env *tmp, size_t len)
{
	size_t	len;
	int		r;
	size_t	*ranks;
	size_t	i;
	size_t	j;

	ranks = malloc(sizeof(int) * (len + 1));
	i = 0;
	j = 0;
	while (tmp->key[i])
	{
		if (tmp->key[i][ft_strlen(tmp->key[i] - 1)] != '=')
		{
			r = find_var_rank(tmp->key[i]);
			if (r != -1)
				ranks[j++] = (size_t *)&r;
		}
		++i;
	}
	return (ranks);
}

void	ft_unset(char *command, char *arg)
{
	printf("\t>>>DEBUT FT_UNSET<<<\n");
	t_env	*tmp;
	int		*ranks;
	size_t	len;

	tmp = t_env(ft_split(arg, ' '));
	if (tmp == NULL)
		return ;
	len = len_list(tmp);
	ranks = find_ranks(tmp, len);
	delete_items(ranks, len);
	printf("\t>>>FIN FT_UNSET<<<\n");
}
