/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_environment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:30:55 by anvincen          #+#    #+#             */
/*   Updated: 2023/07/19 17:40:35 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*check_inputs(char **var)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (var[i])
	{
		if (ft_isalpha(var[i][0]) == 0 && var[i][0] != '_')
			return (var[i]);
		j = 1;
		while (var[i][j])
		{
			if (ft_isalnum(var[i][j]) == 0 && var[i][j] != '_')
				return (var[i]);
			++j;
		}
		++i;
	}
	return (NULL);
}
