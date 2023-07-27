/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/27 15:54:38 by anvincen         ###   ########.fr       */
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

bool	update_pwd(t_data *data, bool a)
{
	char	cwd[PATH_MAX];
	char	*n_v;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (1);
	if (a == 0)
		n_v = ft_strjoin("PWD=", cwd);
	else
		n_v = ft_strjoin("OLDPWD=", cwd);
	if (n_v == NULL)
		return (1);
	if (a == 0)
		data->env = replace_value(data->env, get_var(data->env, "PWD"), n_v);
	else
		data->env = replace_value(data->env, get_var(data->env, "OLDPWD"), n_v);
	free(n_v);
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
		if (update_pwd(data, 1) != 0)
			return (1);
		if (arg == NULL || ft_strlen(arg) == 0 || ft_strcmp(arg, "~") == 1)
		{
			if (chdir(getenv("HOME")) != 0)
				return (1);
			else
				return (0);
		}
		else if (ft_strcmp(arg, "~/") == 1 && ft_strlen(arg) >= 2)
			arg = get_complete_path(arg);
		if (chdir(arg) != 0 || update_pwd(data, 0) != 0)
		{
			printf("bash: cd: %s: No such file or directory\n", data->arg);
			return (1);
		}
	}
	return (0);
}
