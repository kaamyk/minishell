/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/28 10:40:26 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// bool	check_nb_args(char *arg)
// {
// 	size_t	i;

// 	i = 0;
// 	while (arg[i] == ' ')
// 		++i;
// 	while (arg[i])
// 	{
// 		if (arg[i] == ' ')
// 		{
// 			while (arg[i] == ' ' && arg[i + 1])
// 			{
// 				if (arg[i + 1] != ' ')
// 					return (true);
// 				++i;
// 			}
// 		}
// 		++i;
// 	}
// 	return (false);
// }

bool	check_nb_args(char *arg, int *exit)
{
	size_t	i;
	char	c;

	i = 0;
	while (*exit == 0 && arg[i])
	{
		if ((arg[i] == '"' || arg[i] == '\''))
		{
			c = arg[i++];
			while (arg[i] && arg[i] != c)
				++i;
		}
		if (arg[i] == ' ')
		{
			while (*exit == 0 && arg[i] == ' ' && arg[i + 1])
			{
				if (arg[i + 1] != ' ')
					*exit = 1;
				++i;
			}
		}
		++i;
	}
	return (*exit);
}

char	*get_complete_path(char *arg, int *exit)
{
	char	*res;

	res = ft_strjoin(getenv("HOME"), arg + 1);
	if (res == NULL)
	{
		*exit = 1;
		return (NULL);
	}
	return (res);
}

bool	update_pwd(t_data *data, bool a, int *exit)
{
	char	cwd[PATH_MAX];
	char	*n_v;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		*exit = 1;
		return (1);
	}
	if (a == 0)
		n_v = ft_strjoin("PWD=", cwd);
	else
		n_v = ft_strjoin("OLDPWD=", cwd);
	if (n_v == NULL)
	{
		*exit = 1;
		return (1);
	}
	if (a == 0)
		data->env = replace_value(data->env, get_var(data->env, "PWD"), n_v);
	else
		data->env = replace_value(data->env, get_var(data->env, "OLDPWD"), n_v);
	if (data->env == NULL)
		*exit = 1;
	free(n_v);
	return (*exit);
}

bool	ft_cd(t_data *data)
{
	char	*arg;
	int		*exit;

	arg = data->arg;
	exit = &data->exit_code;
	if (arg != NULL && check_nb_args(arg, exit) != 0)
		printf("bash: cd: too many arguments\n");
	else
	{
		if (update_pwd(data, 1, exit) != 0)
			return (*exit);
		if (arg == NULL || ft_strlen(arg) == 0 || ft_strcmp(arg, "~") == 1)
		{
			if (chdir(getenv("HOME")) != 0)
				*exit = 1;
		}
		else if (*exit == 0 && ft_strcmp(arg, "~/") == 1 && ft_strlen(arg) >= 2)
			arg = get_complete_path(arg, exit);
		if (*exit == 0 && (chdir(arg) != 0 || update_pwd(data, 0, exit) != 0))
		{
			printf("bash: cd: %s: No such file or directory\n", data->arg);
			*exit = 1;
		}
	}
	return (*exit);
}
