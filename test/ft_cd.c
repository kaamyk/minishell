/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/20 14:59:40 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

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

bool	update_pwd(t_data *data)
{
	char	cwd[PATH_MAX];
	char	*n_var;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (1);
	n_var = ft_strjoin("PWD=", cwd);
	if (n_var == NULL)
		return (1);
	data->env = replace_value(data->env, get_var(data->env, "PWD"), n_var);
	free(n_var);
	return (0);
}

bool	ft_cd(t_data *data)
{
	char	*arg;

	arg = data->arg;
	if (arg != NULL && check_nb_args(arg) != 0)
		return (1);
	else
	{
		if (arg == NULL || ft_strlen(arg) == 1
			|| ft_strcmp(arg, "~") == 1)
		{
			if (chdir(getenv("HOME")) != 0)
				return (1);
			return (0);
		}
		if (ft_strcmp(arg, "~/") == 1 && ft_strlen(arg) >= 2)
			arg = get_complete_path(arg);
		if (chdir(arg) != 0 || update_pwd(data) != 0)
			return (1);
		printf("\tft_cd |=>data-<env = %p\n", data->env);
	}
	return (0);
}
