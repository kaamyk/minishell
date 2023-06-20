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

int	ft_access(char *file)
{
	int	result;

	result = access(file, F_OK);
	if (result != 0)
		ft_error(NO_SUCH, file, 0);
	return (result);
}

void	ft_classify_str4(t_data *data, char *file, int signe)
{
	if (signe == 1)
	{
		ft_redirection(data, data->result, file, true);
	}
	else if (signe == 2 && ft_access(file) == 0)
	{
		ft_redirection2(data, file);
	}
	else if (signe == 3)
	{
		ft_redirection(data, data->result, file, false);
	}
	else if (signe == 4)
		ft_redirection4(data, file);
	free(file);
}

void	ft_classify_str3(t_data *data, char *str)
{
	char	*arg;

	if (str[0] == '>' && str[1] != '>')
	{
		arg = ft_classify_str2(str, '>');
		ft_classify_str4(data, arg, 1);
	}
	else if (str[0] == '<' && str[1] != '<')
	{
		arg = ft_classify_str2(str, '<');
		ft_classify_str4(data, arg, 2);
	}
	else if (str[0] == '>' && str[1] == '>')
	{
		arg = ft_classify_str2(str, '>');
		ft_classify_str4(data, arg, 3);
	}
	else if (str[0] == '<' && str[1] == '<')
	{
		arg = ft_classify_str2(str, '<');
		ft_classify_str4(data, arg, 4);
	}
}

char	*ft_classify_str2(char *str, char c)
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

void	ft_classify_str(t_data *data, char *str)
{
	char	*arg;

	if (str[0] != '>' && str[0] != '<' && str[0] != '|')
	{
		ft_get_cmd(data, str);
	}
	else if (str[0] == '|')
	{
		arg = ft_classify_str2(str, '|');
		ft_get_cmd(data, arg);
		free(arg);
	}
	else
		ft_classify_str3(data, str);
}
