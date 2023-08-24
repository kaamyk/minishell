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

void	ft_redirection_input(t_data *data, int i, int *fd, int tmp_fd)
{
	char	*file;
	char	*str;
	int		fd_file;

	file = ft_find_str(data->file);
	if (!file)
	{
		printf("bash: : No such file or directory");
		return ;
	}
	close(fd[0]);
	close(fd[1]);
	if (data->tab_cmd[i][1] == '>')
		fd_file = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		fd_file = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd_file < 0)
	{
		printf("bash: : No such file or directory");
		free(file);
		return ;
	}
	if (i != 0)
	{
		dup2(fd_file, STDOUT_FILENO);
		str = ft_read_pipe(tmp_fd);
		if (str)
		{
			printf("%s\n", str);
			free(str);
		}
	}
	close(fd_file);
	free(file);
}
