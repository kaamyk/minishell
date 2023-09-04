/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:52:04 by xuluu             #+#    #+#             */
/*   Updated: 2023/08/30 16:33:14 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**********************************/
/* Create [data->cmd] [data->arg] */
/**********************************/

void	ft_copy_character_in_quote(char *str, char *new_str, int *m)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != str[0])
		{
			new_str[*m] = str[i];
			(*m)++;
		}
		i++;
	}
}

char	*ft_create_cmd(char *str, int i, int m, int *add)
{
	char	*str_quote;
	char	*new_str;

	new_str = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!new_str)
		return (0);
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			str_quote = ft_get_str_without_space(&str[i]);
			ft_copy_character_in_quote(str_quote, new_str, &m);
			i += ft_strlen(str_quote);
			free(str_quote);
		}
		else
		{
			new_str[m] = str[i];
			m++;
			i++;
		}
	}
	new_str[m] = 0;
	*add = i;
	return (new_str);
}

char	*ft_delete_space_begin(char *str)
{
	int		i;
	int		m;
	char	*new_str;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i])
		return (0);
	new_str = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!new_str)
		return (0);
	m = 0;
	while (str[i])
	{
		new_str[m] = str[i];
		m++;
		i++;
	}
	new_str[m] = 0;
	free(str);
	return (new_str);
}

char	*ft_create_arg(char *str)
{
	int		i;
	int		m;
	char	*new_str;

	new_str = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!new_str)
		return (0);
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	m = 0;
	while (str[i])
	{
		new_str[m] = str[i];
		m++;
		i++;
	}
	new_str[m] = 0;
	return (new_str);
}

void	ft_get_cmd(t_data *data, char *str)
{
	int	i;

	if (str)
	{
		data->cmd = ft_create_cmd(str, 0, 0, &i);
		data->arg = 0;
		if (str[i])
			data->arg = ft_create_arg(&str[i]);
	}
}
