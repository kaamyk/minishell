/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:30:55 by anvincen          #+#    #+#             */
/*   Updated: 2023/06/07 18:42:16 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*g_env = NULL;

char	*get_line(char *str)
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

void	ft_read_line(char *line)
{
	if (ft_strchr(line, ';') != 0)
		ft_get_command2(line, ';');
	else if (ft_strchr(line, '|') != 0)
		ft_get_command2(line, '|');
	else
		ft_get_command(line);
}

t_env	*init_env(char **env)
{
	t_env	*n_env;

	if (env == NULL)
		return (NULL);
	n_env = malloc(sizeof(t_env));
	n_env->len = len_list(env);
	//g_env->env = dup_list(env);
	n_env->key = init_keys(env, n_env->len);
	n_env->value = init_values(env);
	return (n_env);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;

	//ft_signal();
	(void) argc;
	(void) argv;
	g_env = init_env(env);
	while (1)
	{
		line = get_line("$>");
		if (!line)
		{
			free_list((void **)g_env->key);
			free_list((void **)g_env->value);
			free(g_env);
			break ;
		}
		ft_read_line(line);
	}
}
