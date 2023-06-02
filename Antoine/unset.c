/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/02 18:37:48 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**g_env;

char	**isolate_keys(char **inputs, size_t l_inputs)
{
	char	**res;
	size_t	rank;
	size_t	i;

	i = 0;
	res = malloc(sizeof(char *) * (l_inputs + 1));
	while (inputs[i])
	{
		rank = rank_char(inputs[i], '=');
		printf("	>>> rank == %ld <<<\n", rank);
		res[i] = ft_calloc(rank + 1, sizeof(char));
		ft_strlcpy(res[i], inputs[i], rank);
		printf("	>>> res[%ld] == %s <<<\n", i, res[i]);
		++i;
	}
	res[i] = NULL;
	return (res);
}

int	*find_ranks(char **inputs, size_t l_inputs)
{
	char	**keys;
	int		*rank;
	size_t	i;
	size_t	j;

	rank = malloc(sizeof(int) * (l_inputs + 1));
	if (rank == NULL)
		return (NULL);
	rank[l_inputs] = -1;
	keys = isolate_keys(inputs, l_inputs);
	i = 0;
	while (keys[i])
	{
		j = 0;
		while (g_env[j])
		{
			if (ft_strncmp(g_env[j], keys[i], ft_strlen(keys[i])) == 0)
			{
				rank[i] = j;
				break ;
			}
			++j;
		}
		++i;
	}
	return (rank);
}

char	**delete_items_list(int *ranks)
{
	size_t	i;

	i = 0;
	while (ranks[i] >= 0)
	{
		printf("g_env[%d] == %s\n", ranks[i], g_env[ranks[i]]);
		++i;
	}
	return (NULL);
}

char	**ft_unset(char *command, char *arg)
{
	char	**n_env;
	char	**inputs;
	int		*ranks;
	size_t	l_inputs;

	(void)command;
	printf("	>>> DEBUT <<<\n");
	print_list(g_env);
	inputs = ft_split(arg, ' ');
	if (inputs == NULL)
		return (NULL);
	l_inputs = len_list(inputs);
	n_env = malloc(sizeof(char *) * (len_list(g_env) - l_inputs));
	if (n_env == NULL)
	{
		free_list((void **)inputs);
		return (NULL);
	}
	ranks = find_ranks(inputs, l_inputs);
	if (ranks == NULL)
	{
		free_list((void **)inputs);
		free_list((void **)n_env);
		return (NULL);
	}
	n_env = delete_items_list(ranks);
	// printf("	>>> FIN <<<\n");
	// print_list(g_env);
	return (NULL);
	//g_env = n_env;
}
