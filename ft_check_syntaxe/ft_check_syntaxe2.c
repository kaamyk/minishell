/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:15:47 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/25 17:11:56 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_single_double_quote(char *str, int i)
{
	char	c;

	c = str[i];
	i++;
	while (str[i] != 0 && str[i] != c)
		i++;
	return (i);
}

bool	ft_check_open_quotes(t_data *data)
{
	int	i;

	i = 0;
	while (data->str[i])
	{
		if (data->str[i] == '\'')
			i = ft_single_double_quote(data->str, i);
		else if (data->str[i] == '"')
			i = ft_single_double_quote(data->str, i);
		if (data->str[i] == 0)
		{
			data->exit_code = 130;
			ft_error(SYNTAXE, &data->str[i], 0);
			return (true);
		}
		i++;
	}
	return (false);
}
