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

void	ft_write_in_file(t_data *data, int i, int tmp_fd, char *file)
{
	int		fd_file;
	char	*str;

	if (data->tab_cmd[i][1] == '>')
		fd_file = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		fd_file = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
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

void	ft_redirection_input(t_data *data, int i, int *fd, int tmp_fd)
{
	char	*file;
	char	*file_direction;

	file = ft_find_str(data->file);
	file_direction = ft_find_str(data->file_direction);
	close(fd[0]);
	close(fd[1]);
	if (i == data->id || ft_compare_str(file, file_direction) == false)
	{
		free(file_direction);
		ft_write_in_file(data, i, tmp_fd, file);
	}
	else
		free(file_direction);
	free(file);
}

/*
Chercher la position de la file direction dans la commande
*/
bool	ft_check_outfile(t_data *data)
{
	int		i;
	char	**tab;

	tab = data->tab_cmd;
	i = 0;
	while (tab[i])
	{
		if (tab[i][0] == '>')
		{
			data->id = i;
			data->file_direction = data->tab_cmd[i];
			return (1);
		}
		i++;
	}
	return (0);
}
