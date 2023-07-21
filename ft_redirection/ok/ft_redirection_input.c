/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:52:17 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/17 15:52:52 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/************************/
/* Redirections [>] [>>]*/
/************************/

void	ft_write(t_data *data, char	*file, bool s_double)
{
	pid_t	pid;
	int		fd;

	pid = fork();
	if (pid == 0)
	{
		if (s_double == true)
			fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
		else
			fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		dup2(fd, STDOUT_FILENO);
		execute(data);
		free(file);
		ft_free_end(data);
		exit(data->exit_code);
	}
	waitpid(pid, &data->exit_code, 0);
	ft_exit_code(data);
}

bool	ft_redirection_input(t_data *data, int i)
{
	char	*file;

	if (data->tab_cmd[i][0] == '>')
	{
		data->file = data->tab_cmd[i];
		if (i > 0 && data->tab_cmd[i - 1][0] == '>')
			data->str = NULL;
		file = ft_find_str(data->file);
		if (data->tab_cmd[i][1] == '>')
			ft_write(data, file, true);
		else
			ft_write(data, file, false);
		free(file);
		return (1);
	}
	return (0);
}
