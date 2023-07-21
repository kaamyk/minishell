/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:51:47 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/21 09:20:07 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

bool	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if ((s1 == NULL) ^ (s2 == NULL))
		return (false);
	else if (s1 == NULL && s1 == NULL)
		return (true);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (false);
		i++;
	}
	if (s1[i] == 0 && s2[i] == 0)
		return (true);
	else
		return (false);
}

char	*take_input(char *str)
{
	char	*line;

	line = NULL;
	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline(str);
	if (line)
		add_history(line);
	return (line);
}

void	ft_execute(t_data *data)
{
	if (ft_strcmp(data->cmd, "export") == 1)
		ft_export(data);
	else if (ft_strcmp(data->cmd, "env") == 1)
		ft_env(data);
	else if (ft_strcmp(data->cmd, "unset") == 1)
		ft_unset(data);
	else if (ft_strcmp(data->cmd, "cd") == 1)
		ft_cd(data);
	else if (ft_strcmp(data->cmd, "pwd") == 1)
		ft_pwd();
	else if (ft_strcmp(data->cmd, "echo") == 1)
		ft_echo(data);
	else
		printf("command unknown\n");
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	data.env = dup_list(env);
	data.exit_code = 0;
	while (1)
	{
		data.cmd = take_input("COMMAND\t$>");
		data.arg = take_input("ARG\t$>");
		if (data.cmd == NULL || ft_strlen(data.cmd) == 0)
			break ;
		ft_execute(&data);
		if (data.cmd == NULL)
			break ;
	}
	free_list(data.env);
	return (0);
}
