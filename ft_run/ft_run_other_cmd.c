/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_other_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:05:42 by xuluu             #+#    #+#             */
/*   Updated: 2023/09/01 11:29:13 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/***********************************/
/*   Execute the other commands    */
/* [ls] [grep] [cat] [wc -c] [...] */
/***********************************/

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

char	*handle_path(t_data *data, char *path, char *str, int is_exist)
{
	if (is_exist != -1)
	{
		if ((ft_strncmp(str, "/bin", 4) == 0
				&& ft_strlen(str) > 6 && str[4] == '/' && str[5] != 0)
			|| (ft_strcmp(str, "./minishell") == true))
			path = ft_copy_str(str);
		else
			data->exit_code = 126;
	}
	else
		data->exit_code = 127;
	return (path);
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
		path = handle_path(data, path, str, is_exist);
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
	int		status;

	pid = fork();
	if (pid == 0)
	{
		child_signal();
		ft_other_cmd_with_pipe(data);
		ft_free_end(data);
		exit(data->exit_code);
	}
	parent_signal(0);
	waitpid(pid, &status, 0);
	parent_signal(1);
	if (WIFSIGNALED(status))
		data->exit_code = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
	else
		data->exit_code = status;
}
