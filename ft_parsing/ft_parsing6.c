/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:57:22 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/07 12:58:23 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/****************************/
/* Put the command at first */
/****************************/

void	ft_partie1(t_data *data, char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	data->partie1 = (char *)malloc((len + 1) * sizeof(char));
	if (!data->partie1)
		return ;
	i = 0;
	while (i < len)
	{
		data->partie1[i] = str[i];
		i++;
	}
	data->partie1[i] = 0;
}

void	ft_partie2(t_data *data, char *str)
{
	int		i;
	int		len;

	i = 0;
	while (str[i] != 0
		&& (str[i] == str[0]
			|| str[i] == ' '))
		i++;
	while (str[i] != 0 && str[i] != ' ' && str[i] != '>' && str[i] != '<')
		i++;
	len = i;
	data->partie2 = (char *)malloc((len + 1) * sizeof(char));
	if (!data->partie2)
		return ;
	i = 0;
	while (i < len)
	{
		data->partie2[i] = str[i];
		i++;
	}
	data->partie2[i] = 0;
	ft_partie1(data, &str[i]);
}

/*
[> file echo salut] --> [echo salut > file]
*/
char	*ft_put_cmd_at_first(t_data *data, char *str)
{
	char	*tmp;
	char	*new_str;

	ft_partie2(data, str);
	new_str = ft_strjoin(data->partie1, " ");
	tmp = new_str;
	new_str = ft_strjoin(new_str, data->partie2);
	free(tmp);
	free(data->partie1);
	free(data->partie2);
	new_str = ft_delete_space(new_str);
	return (new_str);
}
