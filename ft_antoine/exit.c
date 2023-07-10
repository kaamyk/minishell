/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/10 17:07:13 by antoine          ###   ########.fr       */
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
	while (arg[i] != 0)
	{
		if (ft_isdigit(arg[i]) == 0)
			return (1);
		++i;
	}
	return (0);
}

void	ft_exit(t_data *data)
{
	printf(">>> ft_exit\n");
	if (data->arg == NULL || ft_strlen(data->arg) == 0)
		exit (0);
	else if (check_nb_arg(data->arg) != 0)
	{
		printf("bash: exit: too many arguments\n");
		return ;
	}
	else if (check_alnum(data->arg) != 0)
	{
		printf("bash: exit: %s: numeric argument required\n", data->arg);
		exit (2);
	}
	exit (ft_atoi(data->arg));
}
