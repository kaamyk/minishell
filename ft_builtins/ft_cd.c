/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/08/31 10:00:17 by anvincen         ###   ########.fr       */
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

char	*get_complete_path(char **env, char *arg, int *exit)
{
	char	*res;
	char	*home;

	home = ft_get_value(env, "$HOME");
	res = ft_strjoin(home, arg + 1);
	free(home);
	if (res == NULL)
	{
		*exit = 1;
		return (NULL);
	}
	free(arg);
	return (res);
}

bool	cd_home(t_data *data, int *exit)
{
	char	*home_path;

	home_path = ft_get_value(data->env, "$HOME");
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
	char	cwd[PATH_MAX];

	arg = data->arg;
	exit = &data->exit_code;
	if (arg != NULL && check_nb_args(arg, exit) != 0)
		write(STDERR_FILENO, "bash: cd: too much argument\n", 29);
	if (update_oldpwd(data, exit) == 0)
	{
		if (arg == NULL || ft_strcmp(arg, "~") || ft_strcmp(arg, "~/"))
			cd_home(data, exit);
		else if (getcwd(cwd, sizeof(cwd)) == NULL)
			perror("cd: getcwd: cannot access parent directories");
		if (*exit == 0)
		{
			if (data->arg && chdir(data->arg) != 0)
			{
				perror("bash: cd");
				*exit = 1;
			}
		}
		update_pwd(data, exit);
	}
	return (*exit);
}

// mkdir a/ && mkdir a/b && cd a/b && rm -r ../../a/
