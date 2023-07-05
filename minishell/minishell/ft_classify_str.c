/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_classify_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:07:54 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/13 17:08:50 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_access(char *file)
{
	int	result;
	int	error;

	error = 0;
	result = access(file, F_OK);
	if (result != 0)
		error++;
	result = access(file, R_OK);
	if (result != 0)
		error++;
	if (error != 0)
	{
		perror(file);
		return (1);
	}
	return (0);
}

void	ft_classify_str4(t_data *data, char *file, int signe)
{
	if (signe == 1)
	{
		ft_redirection(data, data->input, file, true);
	}
	else if (signe == 2 && ft_access(file) == false)
	{
		ft_redirection2(data, file);
	}
	else if (signe == 3)
	{
		ft_redirection(data, data->input, file, false);
	}
	else
		data->exit_code = 2;
	free(file);
}

char	*ft_find_str(char *str, char c)
{
	char	*string;
	int		i;

	string = NULL;
	i = 0;
	while (str[i] != 0
		&& (str[i] == c || str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] != 0)
		string = ft_copy_str(&str[i]);
	return (string);
}

void	ft_classify_str3(t_data *data, char *str)
{
	char	*arg;

	if (str[0] == '>' && str[1] != '>')
	{
		arg = ft_find_str(str, '>');
		ft_classify_str4(data, arg, 1);
	}
	else if (str[0] == '<' && str[1] != '<')
	{
		arg = ft_find_str(str, '<');
		ft_classify_str4(data, arg, 2);
	}
	else if (str[0] == '>' && str[1] == '>')
	{
		arg = ft_find_str(str, '>');
		ft_classify_str4(data, arg, 3);
	}
}

void	ft_classify_str(t_data *data, char *str)
{
	if (str[0] == '>' || str[0] == '<')
		ft_classify_str3(data, str);
}
