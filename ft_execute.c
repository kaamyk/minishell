/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:51:33 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/23 17:52:23 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
[|] [| grep h] [pwd]
*/
void	ft_execute_without_pipe2(t_data *data, char **tab, int i)
{
	char	*tmp;

	if (tab[i][0] == '|' && ft_strlen(tab[i]) == 1)
		data->str = NULL;
	else
	{
		if (tab[i][0] == '|')
		{
			tmp = tab[i];
			tab[i] = ft_copy_str(&tab[i][2]);
			free(tmp);
		}
		tab[i] = ft_wildcards(data, tab[i]);
		data->str = tab[i];
		if ((tab[i + 1] != 0 && tab[i + 1][0] != '>')
			|| tab[i + 1] == 0)
			ft_pipex(data);
		else if (data->s_heredoc == true)
			child_process(data);
	}
}

void	ft_execute_without_pipe(t_data *data)
{
	int		i;
	char	**tab;

	if (data->nb_cmd > 1)
		data->print = false;
	tab = data->tab_cmd;
	data->file = NULL;
	data->str = NULL;
	data->output = NULL;
	data->s_heredoc = false;
	i = 0;
	while (tab[i])
	{
		if (tab[i + 1] == 0)
			data->print = true;
		if (ft_redirection_output(data, tab[i]) == false
			&& ft_redirection_input(data, i) == false)
		{
			ft_execute_without_pipe2(data, tab, i);
		}
		i++;
	}
	free(data->output);
}

/*
Run in the pipe
if (<< e wc -c)
else if (pwd | grep h | wc -c)
else (...)
--> run and stop program
*/
void	ft_execute_with_pipe(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_execute_without_pipe(data);
		ft_free_end(data);
		exit(data->exit_code);
	}
	waitpid(pid, &data->exit_code, 0);
	ft_exit_code(data);
}

/*
[cd] [exit] [export + arg] [unset + arg] without pipe
ex: << e export salut > file
--> change the value in the envp
*/
void	ft_execute_cmd_without_pipe(t_data *data)
{
	int		i;
	char	**tab;

	tab = data->tab_cmd;
	i = 0;
	while (tab[i])
	{
		if (tab[i][0] != '>' && tab[i][0] != '<')
		{
			data->str = tab[i];
			ft_get_cmd(data, data->str);
			if (ft_compare_str(data->cmd, "cd") == true)
				ft_cd(data);
			else if (ft_compare_str(data->cmd, "exit") == true)
				ft_exit(data);
			else if (ft_compare_str(data->cmd, "export") == true && data->arg)
				ft_export(data);
			else if (ft_compare_str(data->cmd, "unset") == true && data->arg)
				ft_unset(data);
			free(data->cmd);
			free(data->arg);
		}
		i++;
	}
}

/*
Send the commands
*/
void	ft_execute_cmd(t_data *data)
{
	ft_execute_with_pipe(data);
	if (data->s_pipe == false)
		ft_execute_cmd_without_pipe(data);
	ft_free_tab(data->tab_cmd);
}
