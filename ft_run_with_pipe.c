/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_with_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:39:26 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/24 13:41:05 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**************************************/
/*   Execute the commands with pipe   */
/*   [cat | cat | ls]                 */
/*   [pwd | grep h | wc -c]           */
/*   [<< limiter < file wc -c]        */
/*   [ls | wc -l > file >> file2]     */
/*   [...]                            */
/**************************************/

/*
Gerer la redirection [<] [<<]
Gerer les commandes dans le pipe
*/
void	ft_run_in_pipe(t_data *data, int i, int *fd, int tmp_fd)
{
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
	if (i < data->nb_cmd - 1)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (data->s_infile == true && data->tab_cmd[i][0] == '<')
	{
		if (data->tab_cmd[i + 1] == 0 || (data->tab_cmd[i + 1][0] != '<'
			&& data->tab_cmd[i + 1][0] != '|'))
		{
			if (data->tab_cmd[i][1] == '<')
				printf("%s\n", &data->tab_cmd[i][3]);
			else
				ft_redirection_output(data, i);
		}
		else
			data->exit_code = 0;
	}
	else
		ft_run(data, i);
}

/*
Gerer la redirection [>] [>>]
*/
void	ft_run_in_child_process(t_data *data, int i, int *fd, int tmp_fd)
{
	if (data->tab_cmd[i][0] == '>')
	{
		data->file = data->tab_cmd[i];
		ft_redirection_input(data, i, fd, tmp_fd);
	}
	else
		ft_run_in_pipe(data, i, fd, tmp_fd);
}

/*
Envoyer chaque cmd dans le pipe
*/
void	ft_child_process(t_data *data, int *fd, pid_t *pid)
{
	int	i;
	int	tmp_fd;

	tmp_fd = dup(STDIN_FILENO);
	i = 0;
	while (i < data->nb_cmd)
	{
		pipe(fd);
		pid[i] = fork();
		if (pid[i] == 0)
		{
			if (data->tab_cmd[i])
				ft_run_in_child_process(data, i, fd, tmp_fd);
			ft_free_end(data);
			exit(data->exit_code);
		}
		else
		{
			close(fd[1]);
			close(tmp_fd);
			tmp_fd = fd[0];
		}
		i++;
	}
	close(tmp_fd);
}

/*
Processus parent attend les enfants finish
*/
void	ft_run_cmd_with_pipe(t_data *data)
{
	int		i;
	int		fd[2];
	pid_t	*pid;

	pid = (pid_t *)malloc((data->nb_cmd) * sizeof(pid_t));
	if (!pid)
		return ;
	ft_child_process(data, fd, pid);
	i = 0;
	while (i < data->nb_cmd)
	{
		waitpid(pid[i], &data->exit_code, 0);
		ft_exit_code(data);
		ft_check_exit_code(data, i);
		i++;
	}
	free(pid);
}
