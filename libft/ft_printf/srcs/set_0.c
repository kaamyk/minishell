/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:46:39 by anvincen          #+#    #+#             */
/*   Updated: 2023/01/25 17:18:06 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*set_0(char *res, int *field, int *n)
{
	int	i;
	int	len;

	if (!res)
		res = ft_calloc(*field + 1, 1);
	if (!res)
		return (NULL);
	i = 0;
	if (*n < 0)
	{
		res[0] = '-';
		*n *= -1;
		++i;
	}
	len = ft_nblen(*n);
	while (i < *field - len)
	{
		if (!res[i])
			res[i] = '0';
		++i;
	}
	return (res);
}

void	print_0x(char *par, char **res, int field, size_t n)
{
	int	len_n;

	len_n = ft_nblen_hex(n);
	if (n > 0 && !ft_strchr(par, '0') && !ft_strchr(par, '#'))
	{
		res[0][0] = '0';
		if (ft_strchr(par, 'x'))
			res[0][1] = 'x';
		else if (ft_strchr(par, 'X'))
			res[0][1] = 'X';
	}
	else if (n > 0)
	{
		if (len_n + 2 < field)
			res[0][len_n + 2] = '0';
		if (ft_strchr(par, 'x'))
			res[0][1] = 'x';
		else if (ft_strchr(par, 'X'))
			res[0][1] = 'X';
	}
}

void	set_0_u(char *par, char **res, int field, size_t n)
{
	int	i;
	int	len_n;

	if (!*res)
		res = ft_calloc(field + 1, 1);
	if (!res)
		return ;
	len_n = ft_nblen_hex(n);
	i = 0;
	if (ft_strchr_str(par, "0."))
	{
		i = 0;
		while (i < field - len_n)
			if (!res[0][i++])
				res[0][i - 1] = '0';
	}
	else if (ft_strchr(par, '#'))
	{
		i = 2;
		while (!res[0][i] && i < field - (len_n + 2))
			res[0][i++] = ' ';
	}
}
