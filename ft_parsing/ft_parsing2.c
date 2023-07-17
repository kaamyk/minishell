/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:54:38 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/06 16:56:12 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/***********************************/
/* Put the line has quote in a tab */
/***********************************/

/*
create tab string quotes
*/
int	ft_inside_quotes2(t_data *data, char *str, char c_open, char c_close)
{
	int	i;
	int	nb_quote;

	nb_quote = 0;
	i = 0;
	while (str[i])
	{
		if (nb_quote == 2 && (str[i] == ' ' || str[i] == '\t'))
		{
			data->tab_quotes[data->nb_quotes][i] = 0;
			break ;
		}
		if (str[i] == c_open || str[i] == c_close)
			nb_quote++;
		data->tab_quotes[data->nb_quotes][i] = str[i];
		i++;
	}
	data->tab_quotes[data->nb_quotes][i] = 0;
	data->nb_quotes++;
	return (i - 1);
}

int	ft_inside_quotes(t_data *data, char *str, char *new_str, char c_open)
{
	char	c_close;

	data->tab_quotes[data->nb_quotes]
		= (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!data->tab_quotes[data->nb_quotes])
		return (0);
	if (c_open == '(')
		c_close = ')';
	else
		c_close = c_open;
	return (ft_inside_quotes2(data, new_str, c_open, c_close));
}

int	ft_check_quotes_in_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0 && str[i] != ' ' && str[i] != '\t')
	{
		if (str[i] == '|' || str[i] == '&' || str[i] == '>' || str[i] == '<')
			break ;
		if (str[i] == '\'' || str[i] == '"' || str[i] == '(')
			return (str[i]);
		i++;
	}
	return (0);
}

/*
["pwd" > file] --> [ " > file ]
*/
char	*ft_create_string_summary(t_data *data, char *str)
{
	int		i;
	int		m;
	char	c;
	char	*new_str;

	new_str = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!new_str)
		return (0);
	i = -1;
	m = 0;
	while (str[++i])
	{
		c = ft_check_quotes_in_str(&str[i]);
		if (c == '\'' || c == '"' || c == '(')
		{
			new_str[m] = c;
			i += ft_inside_quotes(data, str, &str[i], c);
		}
		else
			new_str[m] = str[i];
		m++;
	}
	new_str[m] = 0;
	data->tab_quotes[data->nb_quotes] = 0;
	return (new_str);
}

char	*ft_create_str_without_quotes(t_data *data, char *str)
{
	char	*new_str;

	data->nb_quotes = 0;
	data->tab_quotes = (char **)malloc
		((ft_strlen(str) + 1) * sizeof(char *));
	if (!data->tab_quotes)
		return (0);
	new_str = ft_create_string_summary(data, str);
	new_str = ft_delete_horizontal_tab(new_str);
	return (new_str);
}
