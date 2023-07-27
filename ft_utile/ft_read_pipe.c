/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:52:17 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/17 15:52:52 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/******************************************/
/* Read in pipe fd[0] and return a string */
/******************************************/

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

char	*ft_read_pipe(int port_read)
{
	char	*res;
	char	*buffer;
	ssize_t	bytes;

	res = NULL;
	buffer = ft_calloc(1024, 1);
	while (1)
	{
		bytes = read(port_read, buffer, 1);
		if (bytes <= 0)
			break ;
		if (res == NULL)
			res = ft_strdup(buffer);
		else
			res = ft_add_string(res, buffer);
	}
	free(buffer);
	close(port_read);
	res = ft_delete_end_new_line(res);
	return (res);
}
