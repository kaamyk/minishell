/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:29:49 by xuluu             #+#    #+#             */
/*   Updated: 2022/11/15 11:25:27 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	check(const char *nptr, int i, int m)
{
	if ((i > 0) && (nptr[i - 1] == '+' || nptr[i - 1] == '-'))
		return (0);
	else if (nptr[i] == '-')
		m *= -1;
	return (m);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	m;
	int	nb;

	i = 0;
	while ((nptr[i] == 32) || (nptr[i] > 8 && nptr[i] < 14))
		i++;
	m = 1;
	while (nptr[i] == '+' || nptr[i] == '-')
	{
		m = check(nptr, i, m);
		i++;
	}
	nb = 0;
	while (ft_isdigit(nptr[i]) != 0)
	{
		nb = (nb * 10) + (nptr[i] - 48);
		i++;
	}
	nb *= m;
	return (nb);
}
