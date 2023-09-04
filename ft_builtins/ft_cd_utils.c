/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/08/30 14:50:14 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_pwd(t_data *data, int *exit)
{
	char	cwd[PATH_MAX];
	char	*n_v;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return ;
	n_v = ft_strjoin("PWD=", cwd);
	if (n_v == NULL)
		return ;
	data->env = rpl_vl(data->env, get_var(data->env, "PWD", 0), n_v);
	if (data->env == NULL)
		*exit = 1;
	free(n_v);
}

bool	update_oldpwd(t_data *data, int *exit)
{
	char	*cwd;
	char	*n_v;

	cwd = ft_get_value(data->env, "$PWD");
	n_v = ft_strjoin("OLDPWD=", cwd);
	free(cwd);
	if (n_v == NULL)
		return (1);
	if (get_var(data->env, "OLDPWD", 0) != NULL)
		data->env = rpl_vl(data->env, get_var(data->env, "OLDPWD", 0), n_v);
	else
		data->env = add_variable(data->env, n_v);
	if (data->env == NULL)
		*exit = 1;
	free(n_v);
	return (*exit);
}
