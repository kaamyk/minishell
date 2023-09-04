/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_output2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:35:05 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/20 11:35:42 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/************************************/
/* Get output of the redirection < */
/************************************/

char	*ft_get_line2(int fd, char *line)
{
	int		i;
	int		byte;
	char	buf;

	byte = 1;
	i = 0;
	while (byte > 0)
	{
		byte = read(fd, &buf, BUFFER_SIZE - BUFFER_SIZE + 1);
		if (byte == 0)
			break ;
		line[i++] = buf;
		if (buf == '\n')
			break ;
	}
	line[i] = 0;
	if (byte == -1 || i == 0)
	{
		free(line);
		return (0);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char	*line;

	if (BUFFER_SIZE <= 0)
		return (0);
	line = (char *)malloc(100000 * sizeof(char));
	if (!line)
		return (0);
	return (ft_get_line2(fd, line));
}

char	*ft_redirection22(int fd)
{
	int		i;
	char	*line;
	char	*str;

	line = get_next_line(fd);
	i = 0;
	str = NULL;
	while (line)
	{
		str = ft_creer_big_string(str, line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (str);
}

char	*ft_redirection2(t_data *data, char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		data->exit_code = 1;
		if (ft_strlen(file) < 1)
		{
			data->exit_code = 0;
			printf("bash: : No such file or directory\n");
		}
		return (0);
	}
	return (ft_redirection22(fd));
}
