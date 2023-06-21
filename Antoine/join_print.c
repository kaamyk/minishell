/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/21 09:27:29 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env;

char	*ft_delete_end_new_line(char *str)
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

char	*join_print(int *fd)
{
	char	*res;
	char	*buffer;
	char	*tmp;
	ssize_t	bytes;

	res = NULL;
	close(fd[1]);
	buffer = ft_calloc(1024, 1);
	while (1)
	{
		bytes = read(fd[0], buffer, 1);
		tmp = res;
		if (bytes <= 0)
			break ;
		if (res == NULL)
			res = ft_strdup(buffer);
		else
			res = ft_add_string(res, buffer);
		free(tmp);
	}
	free(buffer);
	close(fd[0]);
	wait (NULL);
	res = ft_delete_end_new_line(res);
	return (res);
}

char	*read_print(t_data *data, bool (*f)(char *))
{
	int		fd[2];

	data->run = true;
	if (data->print == true)
	{
		f(data->arg);
		return (NULL);
	}
	pipe(fd);
	if (fork() == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		f(data->arg);
		ft_free_all(data);
		exit (0);
	}
	else
		return (join_print(fd));
}
