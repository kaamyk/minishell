/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_other_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:05:42 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/24 13:06:40 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***********************************/
/*   Execute the other commands    */
/* [ls] [grep] [cat] [wc -c] [...] */
/***********************************/

void	ft_exit_code(t_data *data)
{
	if (data->exit_code == 256)
		data->exit_code = 1;
	else if (data->exit_code == 512)
		data->exit_code = 2;
	else if (data->exit_code == 32256)
		data->exit_code = 126;
	else if (data->exit_code == 32512)
		data->exit_code = 127;
}

void	ft_delete_q(t_data *data, char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		tab[i] = ft_delete_quotes(data, tab[i]);
		i++;
	}
}

char	*ft_check_path(t_data *data, char *str)
{
	char	*path;
	int		is_exist;

	path = NULL;
	if (ft_strrchr(str, '/') == 0)
	{
		path = find_path(str, data->env);
		if (!path)
			data->exit_code = 127;
	}
	else
	{
		is_exist = access(str, F_OK | X_OK);
		if (is_exist != -1)
		{
			if (ft_strncmp(str, "/bin", 4) == 0
				&& ft_strlen(str) > 6 && str[4] == '/' && str[5] != 0)
				path = ft_copy_str(str);
			else
				data->exit_code = 126;
		}
		else
			data->exit_code = 127;
	}
	return (path);
}

void	ft_other_cmd_with_pipe(t_data *data)
{
	char	**cmd;
	char	*path;

	cmd = ft_split_mn(data->str, ' ');
	ft_delete_q(data, cmd);
	path = ft_check_path(data, cmd[0]);
	if (path)
	{
		execve(path, cmd, data->env);
		printf("bash: %s\n", strerror(errno));
	}
	if (path)
		free(path);
	ft_free_tab(cmd);
}

void	ft_other_cmd_without_pipe(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_other_cmd_with_pipe(data);
		ft_free_end(data);
		exit(data->exit_code);
	}
	waitpid(pid, &data->exit_code, 0);
	ft_exit_code(data);
}
