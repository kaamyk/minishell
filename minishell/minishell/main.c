/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:51:47 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/26 09:20:55 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*g_env = NULL;

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

void	ft_one_arg(t_data *data, char c)
{
	data->exit_code = 0;
	if (c == '\n'
		|| c == ' '
		|| c == '\t'
		|| c == ':'
		|| c == '!')
		return ;
	else if (c == '$')
	{
		printf("%c\n", c);
	}
	else if (c == '/')
	{
		ft_error(DIRECTORY, "/", NULL);
	}
	else
	{
		ft_error(NOT_FOUND, data->str, 0);
		data->exit_code = 127;
	}
}

void	ft_read_line(t_data *data)
{
	if (ft_check_syntaxe(data) == true)
	{
		free(data->str);
		return ;
	}
	else
	{
		if (ft_strlen(data->str) == 1)
		{
			ft_one_arg(data, data->str[0]);
			free(data->str);
		}
		else
		{
			ft_rewritten_str(data);
			ft_parsing(data);
			ft_execute_cmd(data);
		}
	}
}

// int	main(int ac, char **av, char **env)
// {
// 	t_data	data;

// 	(void)av;
// 	data.exit_code = 0;
// 	if (ac == 1)
// 	{
// 		ft_titre();
// 		data.env = env;
// 		data.s_exit = false;
// 		while (data.s_exit == false)
// 		{
// 			ft_signal();
// 			if (g_env == NULL)
// 				g_env = init_env(env);
// 			data.str = take_input("Minishell$> ");
// 			if (!data.str)
// 				break ;
// 			ft_read_line(&data);
// 			printf("exit_code = %d\n", data.exit_code);
// 			printf("\n");
// 		}
// 	}
// 	free_env(g_env);
// 	return (data.exit_code);
// }

int	main(int ac, char **av, char **env)
{
	char	*line;
	int		len;
	t_data	data;

	if (g_env == NULL)
		g_env = init_env(env);
	if (ac == 2)
	{
		data.env = env;
		data.exit_code = 0;
		len = ft_strlen(av[1]);
		line = (char *)malloc((len + 1) * sizeof(char));
		if (!line)
			return (0);
		line = ft_memcpy(line, av[1], len);
		line[len] = 0;
		data.str = line;
		ft_read_line(&data);
		printf("exit_code = %d\n", data.exit_code);
	}
	free_env(g_env);
	return (data.exit_code);
}
