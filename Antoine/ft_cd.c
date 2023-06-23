/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/23 11:19:10 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	printf("getenv(HOME) == %s\n", getenv("HOME"));
	res = ft_strjoin(getenv("HOME"), arg + 1);
	if (res == NULL)
		return (NULL);
	return (res);
}

bool	ft_cd(t_data *data)
{
	char	*dir;

	if (data->arg != NULL && check_nb_args(data->arg) != 0)
		return (1);
	else
	{
		if (data->arg == NULL || ft_strlen(data->arg) == 0
			|| ft_compare_str(data->arg, "~") == 1)
		{
			if (chdir(getenv("HOME")) != 0)
				return (1);
			return (0);
		}
		else if (ft_strncmp(data->arg, "~/", 2) == 0 && ft_strlen(data->arg) >= 2)
		{
			dir = get_complete_path(data->arg);
			if (chdir(dir) != 0)
			{
				free(dir);
				return (1);
			}
			free(dir);
		}
		else
		{
			if (chdir(data->arg) != 0)
				return (1);
		}
	}
	return (0);
}
