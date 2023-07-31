/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:12:11 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/24 13:12:36 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_find_str_inside_quotes(t_data *data, char *str, char c)
{
	int		i;
	int		check;

	check = 0;
	i = 0;
	while (str[i] && check < 2)
	{
		if (str[i] == c)
			check++;
		else
		{
			data->str_quotes[data->i_quotes] = str[i];
			data->i_quotes++;
		}
		i++;
	}
	if (check == 2)
		i--;
	return (i);
}

void	ft_find_quotes_inside_str(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i += ft_find_str_inside_quotes(data, &str[i], str[i]);
		else
		{
			data->str_quotes[data->i_quotes] = str[i];
			data->i_quotes++;
		}
		if (str[i] == 0)
			break ;
		i++;
	}
	data->str_quotes[data->i_quotes] = 0;
}

char	*ft_delete_quotes(t_data *data, char *str)
{
	if (str)
	{
		data->str_quotes = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
		if (!data->str_quotes)
			return (str);
		data->i_quotes = 0;
		ft_find_quotes_inside_str(data, str);
		free(str);
		str = ft_copy_str(data->str_quotes);
		free(data->str_quotes);
	}
	return (str);
}
