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

void	ft_redirection_input3(int fd_file, int tmp_fd, int i)
{
	char	*str;

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
}

int	ft_redirection_input2(t_data *data, char *file, int i)
{
	int		fd_file;

	if (data->tab_cmd[i][1] == '>')
		fd_file = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		fd_file = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd_file < 0)
	{
		printf("bash: : No such file or directory");
		free(file);
	}
	return (fd_file);
}

void	ft_redirection_input(t_data *data, int i, int *fd, int tmp_fd)
{
	char	*file;
	int		fd_file;

	file = ft_find_limiter(data->file);
	if (!file)
	{
		printf("bash: : No such file or directory");
		return ;
	}
	close(fd[0]);
	close(fd[1]);
	fd_file = ft_redirection_input2(data, file, i);
	if (fd_file < 0)
		return ;
	ft_redirection_input3(fd_file, tmp_fd, i);
	free(file);
}
