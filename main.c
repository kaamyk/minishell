/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:51:47 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/28 10:42:43 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (ft_parsing(data) == true)
			{
				if (data->s_bonus == true)
					ft_run_bonus(data);
				else
					ft_run_cmd(data);
			}
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)av;
	data.exit_code = 0;
	data.env = dup_list(env);
	if (ac == 1)
	{
		ft_titre();
		data.exit_code = 0;
		while (42)
		{
			ft_signal();
			data.str = take_input(KMAG "Minishell$> " RESET);
			if (!data.str)
				break ;
			ft_read_line(&data);
		}
	}
	free_list(data.env);
	return (data.exit_code);
}

// int	main(int ac, char **av, char **env)
// {
// 	char	*line;
// 	int		len;
// 	t_data	data;

// 	if (ac == 2)
// 	{
// 		data.env = dup_list(env);
// 		data.exit_code = 0;
// 		len = ft_strlen(av[1]);
// 		line = (char *)malloc((len + 1) * sizeof(char));
// 		if (!line)
// 			return (0);
// 		line = ft_memcpy(line, av[1], len);
// 		line[len] = 0;
// 		data.str = line;
// 		ft_read_line(&data);
// 		printf("exit_code = %d\n", data.exit_code);
// 		free_list(data.env);
// 	}
// 	return (data.exit_code);
// }
