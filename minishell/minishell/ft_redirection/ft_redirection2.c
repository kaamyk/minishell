/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:35:05 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/20 11:35:42 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	ft_read_file(t_data *data, char *file)
{
	int		fd;
	int		i;
	char	*line;
	char	*str;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	str = NULL;
	while (line)
	{
		str = ft_creer_big_string(i, str, line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	if (data->print == false)
		printf("%s\n", str);
	free(str);
}

void	ft_redirection2(t_data *data, char *file)
{
	ft_read_file(data, file);
}
