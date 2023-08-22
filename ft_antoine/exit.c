/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/08/01 18:16:10 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_nb_arg(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == ' ' && arg[i + 1] != ' ')
			return (1);
		++i;
	}
	return (0);
}

bool	check_alnum(char *arg)
{
	size_t	i;

	i = 0;
	if (ft_isdigit(arg[i]) == 0 && arg[i] != ' ' && arg[i] != '-')
		return (1);
	++i;
	while (arg[i] != 0)
	{
		if (ft_isdigit(arg[i]) == 0 && arg[i] != ' ')
			return (1);
		++i;
	}
	return (0);
}

void	ft_exit(t_data *data)
{
	int	ret;

	if (data->arg == NULL || ft_strlen(data->arg) == 0)
		exit (0);
	else if (check_nb_arg(data->arg) != 0)
	{
		write(STDERR_FILENO, "bash: exit: too many arguments\n", 32);
		data->exit_code = 1;
		return ;
	}
	else if (check_alnum(data->arg) != 0)
	{
		free_list(data->tab_cmd);
		free_list(data->env);
		write(STDERR_FILENO, "bash: exit:", 11);
		write(STDERR_FILENO, data->arg, ft_strlen(data->arg));
		write(STDERR_FILENO, ": numeric argument required\n", 28);
		exit (2);
	}
	ret = ft_atoi(data->arg);
	if (ret < 0)
		exit (255 + ret + 1);
	free_list(data->tab_cmd);
	exit (ft_atoi(data->arg));
}
