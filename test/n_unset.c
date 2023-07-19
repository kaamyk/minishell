/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/19 12:00:04 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_export(t_data *data)
{
	char	**res;
	bool	exit;

	exit = 0;
	if (data->arg == NULL || ft_strlen(data->arg) == 0)
		return (print_env(data->s_env, 1));
	res = init_env(ft_split(data->arg, ' '));
}
