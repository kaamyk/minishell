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

int	ft_inside_quotes(t_data *data, char *str, char c_open)
{
	char	c_close;

	data->tab_quotes[data->nb_quotes]
		= (char *)malloc((ft_strlen(data->str) + 1) * sizeof(char));
	if (!data->tab_quotes[data->nb_quotes])
		return (0);
	if (c_open == '(')
		c_close = ')';
	else
		c_close = c_open;
	return (ft_inside_quotes2(data, str, c_open, c_close));
}

int	ft_check_quotes_in_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0 && str[i] != ' ' && str[i] != '\t')
	{
		if (str[i] == '\'' || str[i] == '"' || str[i] == '(')
			return (str[i]);
		i++;
	}
	return (0);
}

/*
["pwd" > file] --> [ " > file ]
*/
char	*ft_create_string_summary(t_data *data)
{
	int		i;
	int		m;
	char	c;
	char	*str;

	str = (char *)malloc((ft_strlen(data->str) + 1) * sizeof(char));
	if (!str)
		return (0);
	i = -1;
	m = 0;
	while (data->str[++i])
	{
		c = ft_check_quotes_in_str(&data->str[i]);
		if (c == '\'' || c == '"' || c == '(')
		{
			str[m] = c;
			i += ft_inside_quotes(data, &data->str[i], c);
		}
		else
			str[m] = data->str[i];
		m++;
	}
	str[m] = 0;
	data->tab_quotes[data->nb_quotes] = 0;
	return (str);
}

bool	ft_parsing(t_data *data)
{
	char	*str;

	data->nb_quotes = 0;
	data->tab_quotes = (char **)malloc
		((ft_strlen(data->str) + 1) * sizeof(char *));
	if (!data->tab_quotes)
		return (0);
	str = ft_create_string_summary(data);
	str = ft_delete_horizontal_tab(str);
	if (ft_check_syntax_inside(data, str) == true)
	{
		free(str);
		ft_free_tab(data->tab_quotes);
		free(data->str);
		return (0);
	}
	str = ft_step2(data, str);
	data->tab_cmd = ft_create_tab_cmd(data, str);
	free(data->str);
	return (1);
}
