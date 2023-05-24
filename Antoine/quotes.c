/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:15:47 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/24 20:33:46 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	check_open_quotes(char *command, char q)
{
	bool	b;
	size_t	i;

	b = true;
	i = 0;
	while (command[i])
	{
		if (command[i] == q)
			b = !b;
		++i;
	}
	if (b == true)
		return (1);
	return (0);
}

bool	check_first_last_quotes(char *arg, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = len;
	while (j >= 0)
	{
		if (arg[i] != '\'' && arg[i] != '"' && arg[i] != '(')
			++i;
		if (arg[len] != '\'' && arg[len] != '"' && arg[len] != ')')
			--len;
		--j;
	}
	if (arg[i] == arg[len] && check_open_quotes(arg, arg[i]) == true)
		return (true);
	else if (check_open_quotes(arg, '\'') == false
		|| check_open_quotes(arg, '"') == false)
		return (false);
	return (false);
}

char	*ft_quotes(char **command)
{
	char	*tmp;
	char	*str;
	size_t	len;

	len = ft_strlen(command[1]);
	if (check_first_last_quotes(command[1], len) == true
		&& check_open_quotes(command[1], f_q) == true)
	{
		printf("check_quotes == %ld\n", check_open_quotes(command[1], f_q));
		return (command[1]);
	}
	else if (check_open_quotes(arg, '\'') == false
		|| check_open_quotes(arg, '"') == false)
		return (NULL);
	printf("check_quotes == %ld\n", check_open_quotes(command[1], f_q));
	return (command[1]);
}
