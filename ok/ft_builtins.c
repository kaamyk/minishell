/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/26 11:23:28 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***************************************************/
/*              Execute the builtins                */
/* [echo] [pwd] [cd] [exit] [env] [export] [unset] */
/***************************************************/

void	ft_builtins(t_data *data)
{
	if (data->str)
	{
		if (ft_compare_str(data->cmd, "echo") == true)
			ft_echo(data);
		else
		{
			data->exit_code = 0;
			if (ft_compare_str(data->cmd, "pwd") == true)
				ft_pwd();
			else if (ft_compare_str(data->cmd, "exit") == true)
				ft_exit(data);
			else if (ft_compare_str(data->cmd, "env") == true)
				ft_env(data);
			else if (ft_compare_str(data->cmd, "export") == true)
				ft_export(data);
			else if (ft_compare_str(data->cmd, "unset") == true)
				ft_unset(data);
			else if (ft_compare_str(data->cmd, "cd") == true)
				ft_cd(data);
			else
				ft_other_cmd(data);
		}
	}
}
