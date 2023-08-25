/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:39:16 by xuluu             #+#    #+#             */
/*   Updated: 2023/08/25 17:57:37 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***************************************************/
/*              Execute the builtins               */
/* [echo] [pwd] [cd] [exit] [env] [export] [unset] */
/***************************************************/

void	ft_builtins(t_data *data, int id_cmd)
{
	if (id_cmd == 1)
	{
		ft_echo(data);
		data->exit_code = 0;
	}
	else
	{
		data->exit_code = 0;
		if (id_cmd == 2)
			ft_pwd();
		else if (id_cmd == 3)
			ft_cd(data);
		else if (id_cmd == 4)
			ft_exit(data);
		else if (id_cmd == 5)
			ft_env(data);
		else if (id_cmd == 6)
			ft_export(data);
		else if (id_cmd == 7)
			ft_unset(data);
	}
}

bool	ft_check_builtins(t_data *data)
{
	int	id;

	id = 0;
	if (ft_compare_str(data->cmd, "echo") == true)
		id = 1;
	else if (ft_compare_str(data->cmd, "pwd") == true)
		id = 2;
	else if (ft_compare_str(data->cmd, "cd") == true)
		id = 3;
	else if (ft_compare_str(data->cmd, "exit") == true)
		id = 4;
	else if (ft_compare_str(data->cmd, "env") == true)
		id = 5;
	else if (ft_compare_str(data->cmd, "export") == true)
		id = 6;
	else if (ft_compare_str(data->cmd, "unset") == true)
		id = 7;
	if (id != 0)
		ft_builtins(data, id);
	free(data->cmd);
	if (data->arg)
		free(data->arg);
	if (id != 0)
		return (1);
	return (0);
}
