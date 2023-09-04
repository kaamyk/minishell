/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signe_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:36:38 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/28 16:36:40 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**************************/
/* Ignore '$USER "$USER"' */
/**************************/

/*
str_copy = '$USER "$USER"'
*/
void	ft_ignore2(t_data *data, char *str, int len)
{
	int		i;
	char	*new_str;

	new_str = (char *)malloc((len + 1) * sizeof(char));
	if (!new_str)
		return ;
	i = 0;
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = 0;
	ft_add_dollar(data, new_str, true);
}

int	ft_ignore(t_data *data, char *str)
{
	int		i;
	int		nb_signe;

	nb_signe = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			nb_signe++;
		if (nb_signe == 2)
			break ;
		i++;
	}
	ft_ignore2(data, str, i + 1);
	return (i);
}
