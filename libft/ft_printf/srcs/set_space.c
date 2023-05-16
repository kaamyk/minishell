/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:46:39 by anvincen          #+#    #+#             */
/*   Updated: 2023/01/18 13:08:13 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	set_space(char *res, char *par, int *field, int *n)
{
	int	i;
	int	len;

	i = 0;
	len = ft_nblen(*n);
	if (!res)
		return ;
	if (*n < 0)
	{
		if (ft_strchr_str(par, "0-."))
			res[0] = '-';
		else
			res[*field - len] = '-';
		*n *= -1;
	}
	else
	{
		if (ft_strchr_str(par, "0-."))
			res[0] = ' ';
		else
			while (i < *field - len)
				if (!res[i++])
					res[i - 1] = ' ';
	}
}

char	*set_space_u(char *res, char *par, int *field)
{
	int	i;

	i = 0;
	if (!res)
		return (NULL);
	if (ft_strchr(par, '0'))
		res[0] = ' ';
	else
	{
		while (i < *field)
		{
			if (!res[i])
				res[i] = ' ';
			++i;
		}
	}
	return (res);
}
