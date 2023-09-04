/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/08/31 13:08:25 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_nb_arg(char *arg)
{
	size_t	i;
	char	q;

	i = 0;
	q = 0;
	if (arg[0] && (arg[0] == '\'' || arg[0] == '"'))
	{
		q = arg[i++];
		while (arg[i] && arg[i] != q)
			++i;
		if (q && arg[i] == q)
			++i;
	}
	else
	{
		while (arg[i] && ft_isdigit(arg[i]) != 0)
			++i;
	}
	while (arg[i] && arg[i] == ' ')
		++i;
	if (arg[i] != 0)
		return (1);
	return (0);
}

bool	check_arg(char *arg, bool n, bool is_num, char q)
{
	if ((n == 1 && arg[0] == ' ' && arg[0 + 1] && arg[0 + 1] != ' '
			&& arg[1] != 0 && arg[1] != q)
		|| (is_num == 0 && (arg[0] != ' ' && arg[0] != '-'))
		|| (arg[0] == '-' && ft_isdigit(arg[1]) == 0))
		return (1);
	return (0);
}

bool	check_alnum(char *arg)
{
	size_t	i;
	bool	n;
	char	q;
	bool	is_num;

	i = 0;
	n = 0;
	q = ' ';
	if (arg[0] && (arg[0] == '\'' || arg[0] == '"'))
		q = arg[i++];
	while (arg[i] && arg[i] == ' ')
		++i;
	while (arg[i] && arg[i] != q)
	{
		is_num = ft_isdigit(arg[i]);
		if (n == 0 && is_num != 0)
			n = 1;
		if (check_arg(arg + i, n, is_num, q) == 1)
			return (1);
		++i;
	}
	if (n == 0)
		return (1);
	return (0);
}

void	ft_exit(t_data *data)
{
	int		ret;

	if (data->arg == NULL || ft_strlen(data->arg) == 0)
		exit (0);
	if (check_alnum(data->arg) != 0)
	{
		free_list(data->tab_cmd);
		free_list(data->env);
		write(STDERR_FILENO, "bash: exit:", 11);
		write(STDERR_FILENO, data->arg, ft_strlen(data->arg));
		write(STDERR_FILENO, ": numeric argument required\n", 28);
		exit (2);
	}
	if (check_nb_arg(data->arg) != 0)
	{
		write(STDERR_FILENO, "bash: exit: too many arguments\n", 32);
		data->exit_code = 1;
		return ;
	}
	ret = ft_atoi(data->arg + ((data->arg[0] == '"'
					|| data->arg[0] == '\'') & 1));
	if (ret < 0)
		exit (256 + ret);
	free_list(data->tab_cmd);
	exit (ret);
}
