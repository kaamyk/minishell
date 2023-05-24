/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:51:47 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/24 09:10:28 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else if (ft_strchr(line, ' ') != 0)
		ft_get_command2(line, ' ');
	else
	{
		ft_get_command(line);
	}
}

int	main(void)
{
	char	*line;

	ft_signal();
	while (1)
	{
		line = get_line("$>");
		if (!line)
			break ;
		ft_read_line(line);
	}
}

// int	main(int ac, char **av)
// {
// 	char	*line;

// 	if (ac == 2)
// 	{
// 		// ft_read_line(av[1]);
// 		printf("%s\n", av[1]);
// 		line = (char *)malloc(6 * sizeof(char));
// 		if (!line)
// 			return (0);
// 		line[0] = 'l';
// 		line[1] = 's';
// 		line[2] = ' ';
// 		line[3] = 'l';
// 		line[4] = 's';
// 		line[5] = '\0';
// 		ft_read_line(line);
// 	}
// 	return (0);
// }
