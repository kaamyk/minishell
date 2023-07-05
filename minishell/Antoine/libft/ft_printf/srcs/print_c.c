/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:09:46 by anvincen          #+#    #+#             */
/*   Updated: 2023/01/23 11:45:18 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	read_field_c(char **par, int *field)
{
	int	i;

	i = 0;
	while (par[0][i] && !*field)
	{
		if (par[0][i] == '0')
			++i;
		if (ft_isdigit(par[0][i]))
		{
			*field = ft_atoi(*par + i);
			while (ft_isdigit(par[0][i]))
				par[0][i++] = '1';
		}
		++i;
	}
	if (*field == 0)
		*field = 1;
}

void	ft_set_res_c(char *res, char *par, int field, char c)
{
	int	i;

	i = 0;
	if (!ft_strchr(par, '-'))
	{
		while (i < field - 1)
			res[i++] = ' ';
		res[i++] = c;
	}
	else
	{
		if (c != 0)
		{
			res[i++] = c;
			while (i < field)
				res[i++] = ' ';
		}
		else
			while (i < field - 1)
				res[i++] = ' ';
	}
	if (c == 0)
		par[0] = 0;
}

void	print_c(char *par, int c, int *ctr)
{
	char	*res;
	int		field;

	field = 0;
	read_field_c(&par, &field);
	res = ft_calloc(field + 1, 1);
	if (!res)
		return ;
	*ctr += field;
	ft_set_res_c(res, par, field, c);
	ft_print_result(res, field);
	free(res);
}
