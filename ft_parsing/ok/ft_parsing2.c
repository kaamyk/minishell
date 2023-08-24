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

int	ft_inside_quotes(t_data *data, char *str)
{
	int		len;
	char	*find;

	find = ft_get_str_without_space(str);
	data->tab_quotes[data->nb_quotes] = ft_copy_str(find);
	free(find);
	len = ft_strlen(data->tab_quotes[data->nb_quotes]);
	printf("------------> [%s]\n", data->tab_quotes[data->nb_quotes]);
	data->nb_quotes++;
	return (len - 1);
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
	char	*new_str;

	new_str = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!new_str)
		return (0);
	i = 0;
	m = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			new_str[m] = str[i];
			i += ft_inside_quotes(data, &str[i]);
		}
		if (!str[i])
			break ;
		else if (str[i] != '\'' && str[i] != '"')
			new_str[m] = str[i];
		i++;
		m++;
	}
	new_str[m] = 0;
	// printf("new ------------> [%s]\n", new_str);
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
