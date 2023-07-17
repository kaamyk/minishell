/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:47:24 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/17 12:47:29 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**************************************/
/* List current files and directories */
/**************************************/

extern t_env	*g_env;

char	*ft_delete_end_new_line(char *str)
{
	int		i;
	int		len;
	char	*new_str;

	if (!str)
		return (str);
	len = ft_strlen(str) - 1;
	while (len > 0 && str[len] == '\n')
		len--;
	len++;
	new_str = (char *)malloc((len + 1) * sizeof(char));
	if (!new_str)
		return (0);
	i = 0;
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = 0;
	free(str);
	return (new_str);
}

char	*ft_read_pipe(int *fd)
{
	char	*res;
	char	*buffer;
	ssize_t	bytes;

	res = NULL;
	buffer = ft_calloc(1024, 1);
	while (1)
	{
		bytes = read(fd[0], buffer, 1);
		if (bytes <= 0)
			break ;
		if (res == NULL)
			res = ft_strdup(buffer);
		else
			res = ft_add_string(res, buffer);
	}
	free(buffer);
	close(fd[0]);
	res = ft_delete_end_new_line(res);
	return (res);
}

char	*ft_get_current_file_directory(t_data *data, char *directorie)
{
	int		fd[2];
	pid_t	pid;
	char	*str;

	str = NULL;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		data->str = ft_copy_str("ls ");
		data->str = ft_add_string(data->str, directorie);
		execute(data);
		if (data->s_bonus)
		{
			free(data->tab_logic);
			ft_free_tab(data->tab_cmd_logic);
		}
		free(data->str);
		ft_free_tab(data->tab_cmd);
		ft_free_tab(data->tab_wildcards);
		free_env(g_env);
		exit(data->exit_code);
	}
	else
	{
		close(fd[1]);
		str = ft_read_pipe(fd);
		waitpid(pid, &data->exit_code, 0);
		ft_exit_code(data);
	}
	return (str);
}
