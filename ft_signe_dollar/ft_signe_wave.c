/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signe_wave.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:15:57 by xuluu             #+#    #+#             */
/*   Updated: 2023/08/31 09:53:50 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Change ~
*/
int	ft_change_rel_abs_path(t_data *data, char *str)
{
	int		i;
	char	*path;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '$')
			break ;
		i++;
	}
	path = ft_substr(str, 0, i);
	path = get_complete_path(data->env, path, &data->exit_code);
	ft_add_dollar(data, path, false);
	if (str[i] == 0 || str[i] == ' ' || str[i] == '$')
		i--;
	return (i);
}

int	ft_check_signe_wave(t_data *data, char *str, int i)
{
	if ((i > 0 && str[i - 1] != ' ')
		|| (str[i + 1] && str[i + 1] != '/' && str[i + 1] != ' '))
		ft_add_dollar(data, ft_character_to_string(str[i]), false);
	else if (i == 0 || str[i - 1] == ' ')
		i += ft_change_rel_abs_path(data, &str[i]);
	return (i);
}
