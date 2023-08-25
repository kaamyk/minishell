/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntaxe5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:51:26 by xuluu             #+#    #+#             */
/*   Updated: 2023/08/25 12:54:25 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_check_inside_quote(t_data *data)
{
	int		i;
	char	*str;

	i = 0;
	while (data->str[i])
	{
		if (data->str[i] == '"')
		{
			str = ft_get_str_without_space(&(data->str[i]));
			if (str[ft_strlen(str) - 2] == '\\')
			{
				ft_error(SYNTAXE, "\\", 0);
				data->exit_code = 2;
				free(str);
				return (1);
			}
			i += ft_strlen(str);
			free(str);
		}
		else
			i++;
	}
	return (0);
}
