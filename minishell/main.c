/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:51:47 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/23 18:36:58 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_line(void)
{
	char	*line;

	line = NULL;
	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline("$>");
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
	{
		ft_get_command(line);
	}
}

int	main(void)
{
	char		*line;

	ft_signal();
	while (1)
	{
		line = get_line();
		if (!line)
			break ;
		ft_read_line(line);
	}
}

// int	main(int ac, char **av)
// {
// 	if (ac == 2)
// 		ft_read_line(av[1]);
// 	return (0);
// }
