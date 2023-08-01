/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/08/01 09:29:59 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	printf("ft arg == %p\n", arg);
	res = ft_strjoin(getenv("HOME"), arg + 1);
	if (res == NULL)
	{
		*exit = 1;
		return (NULL);
	}
	free(arg);
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

bool	cd_home(t_data *data, int *exit)
{
	char	*home_path;

	home_path = ft_get_value(data->env, "HOME");
	if (home_path != NULL && chdir(home_path) != 0)
	{
		perror("bash: cd");
		*exit = 1;
	}
	else if (home_path == NULL)
	{
		write(STDERR_FILENO, "bash: cd: HOME not set\n", 23);
		*exit = 1;
	}
	free(home_path);
	return (0);
}

bool	ft_cd(t_data *data)
{
	char	*arg;
	int		*exit;

	arg = data->arg;
	printf("arg == %p\n", arg);
	printf("data->arg == %p\n", data->arg);
	exit = &data->exit_code;
	if (arg != NULL && check_nb_args(arg, exit) != 0)
		write(STDERR_FILENO, "bash: cd: too much argument\n", 29);
	if (update_pwd(data, 1, exit) == 0)
	{
		if (arg == NULL || ft_strcmp(arg, "~") || ft_strcmp(arg, "~/"))
			cd_home(data, exit);
		else if (ft_strncmp(arg, "~/", 2) == 0 && ft_strlen(arg) > 2)
			data->arg = get_complete_path(data->arg, exit);
		if (*exit == 0)
		{
			if (data->arg && chdir(data->arg) != 0)
			{
				perror("bash: cd");
				*exit = 1;
				(void) update_pwd(data, 0, exit);
			}
		}
	}
	return (*exit);
}
