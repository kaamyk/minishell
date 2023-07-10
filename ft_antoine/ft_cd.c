/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/21 17:53:34 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_nb_args(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i] == ' ')
		++i;
	while (arg[i])
	{
		if (arg[i] == ' ')
		{
			while (arg[i] == ' ' && arg[i + 1])
			{
				if (arg[i + 1] != ' ')
					return (true);
				++i;
			}
		}
		++i;
	}
	return (false);
}

char	*get_complete_path(char *arg)
{
	char	*res;

	res = ft_strjoin(getenv("HOME"), arg + 1);
	if (res == NULL)
		return (NULL);
	return (res);
}

bool	ft_cd(char *arg)
{
	if (arg != NULL && check_nb_args(arg) != 0)
		return (1);
	else
	{
		if (arg == NULL || ft_strlen(arg) == 0
			|| ft_compare_str(arg, "~") == 1)
		{
			if (chdir(getenv("HOME")) != 0)
				return (1);
			return (0);
		}
		if (ft_strncmp(arg, "~/", 2) == 0 && ft_strlen(arg) >= 2)
			arg = get_complete_path(arg);
		if (chdir(arg) != 0)
			return (1);
	}
	return (0);
}
