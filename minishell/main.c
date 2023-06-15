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
	if (ft_strlen(line) == 0)
	{
		free(line);
		return ;
	}
	line = ft_delete_space(line);
	if (ft_check_open_quotes(line) == true)
	{
		ft_error(SYNTAXE, line, 0);
		free(line);
		return ;
	}
	if (ft_check_syntaxe(line) == false)
	{
		line = ft_split_cmd(line);
	}
	free(line);
}

// int	main(void)
// {
// 	char	*line;

// 	ft_signal();
// 	while (1)
// 	{
// 		line = get_line("$> ");
// 		if (!line)
// 			break ;
// 		ft_read_line(line);
// 	}
// }

int	main(int ac, char **av, char **env)
{
	char	*line;
	int		len;

	if (g_env == NULL)
		g_env = init_env(env);
	if (ac == 2)
	{
		len = ft_strlen(av[1]);
		line = (char *)malloc((len + 1) * sizeof(char));
		if (!line)
			return (0);
		line = ft_memcpy(line, av[1], len);
		line[len] = 0;
		ft_read_line(line);
	}
	free_env(g_env);
	return (0);
}
