/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 16:01:16 by gcollet           #+#    #+#             */
/*   Updated: 2022/02/06 10:25:26 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(void)
{
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}

char	*ft_delete_end_new_line2(char *str)
{
	int		i;
	int		len;
	char	*new_str;

	if (!str)
		return (str);
	len = ft_strlen(str) - 1;
	while (len > 0 && str[len] == '\n')
		len--;
	len++;
	new_str = (char *)malloc((len + 1) * sizeof(char));
	if (!new_str)
		return (0);
	i = 0;
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = 0;
	free(str);
	return (new_str);
}

char	*ft_get_output(int *fd)
{
	char	*res;
	char	*buffer;
	ssize_t	bytes;

	res = NULL;
	close(fd[1]);
	buffer = ft_calloc(1024, 1);
	while (1)
	{
		bytes = read(fd[0], buffer, 1);
		if (bytes <= 0)
			break ;
		if (res == NULL)
			res = ft_strdup(buffer);
		else
			res = ft_add_string(res, buffer);
	}
	free(buffer);
	close(fd[0]);
	res = ft_delete_end_new_line2(res);
	return (res);
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		error();
	return (file);
}
