/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_plus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 16:08:39 by anvincen          #+#    #+#             */
/*   Updated: 2023/01/18 13:10:42 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*set_plus(char *par, char *res, int field, int *n)
{
	int	len;

	if (*n < 0)
	{
		*n *= -1;
		if (ft_strchr_str(par, "0."))
			res[0] = '-';
		else
		{
			len = ft_nblen(*n);
			res[field - len - 1] = '-';
		}
	}
	else
	{
		if (ft_strchr_str(par, "0.-"))
			res[0] = '+';
		else
		{
			len = ft_nblen(*n);
			res[field - len - 1] = '+';
		}
	}
	return (res);
}

char	*set_plus_u(char *res)
{
	if (!res)
		return (NULL);
	res[0] = '+';
	return (res);
}
