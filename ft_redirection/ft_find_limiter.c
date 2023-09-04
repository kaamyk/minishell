/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_limiter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:45:55 by xuluu             #+#    #+#             */
/*   Updated: 2023/08/24 10:46:31 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_delete_space_end(char *str)
{
	int		i;
	int		m;
	char	*new_str;

	new_str = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!new_str)
		return (0);
	i = ft_strlen(str) - 1;
	while (i > 0)
	{
		if (str[i] != ' ')
			break ;
		i--;
	}
	m = 0;
	while (m < i + 1)
	{
		new_str[m] = str[m];
		m++;
	}
	new_str[m] = 0;
	free(str);
	return (new_str);
}

void	ft_find_limiter3(char *str, char *new_str, int *m)
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

void	ft_find_limiter2(char *str, char *new_str)
{
	int		i;
	int		m;
	char	*find;

	i = 0;
	m = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			find = ft_get_str_without_space(&str[i]);
			ft_find_limiter3(find, new_str, &m);
			i += ft_strlen(find);
			free(find);
		}
		if (!str[i] || str[i] == ' ')
			break ;
		if (str[i] != '"' && str[i] != '\'')
		{
			new_str[m] = str[i];
			m++;
			i++;
		}
	}
	new_str[m] = 0;
}

char	*ft_find_limiter(char *str)
{
	int		i;
	char	*new_str;

	i = 1;
	if (str[1] == '<' || str[1] == '>')
		i = 2;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i])
		return (0);
	new_str = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!new_str)
		return (0);
	ft_find_limiter2(&str[i], new_str);
	if (ft_check_space_string(new_str) == 0)
		new_str = ft_delete_space_end(new_str);
	return (new_str);
}
