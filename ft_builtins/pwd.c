/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:51:47 by xuluu             #+#    #+#             */
/*   Updated: 2023/08/30 14:10:44 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_pwd(t_data *data)
{
	char	cwd[PATH_MAX];
	char	*val;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		val = ft_get_value(data->env, "$PWD");
		printf("%s\n", val);
		free(val);
	}
	return (0);
}
