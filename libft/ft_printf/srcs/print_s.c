/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:09:46 by anvincen          #+#    #+#             */
/*   Updated: 2023/01/26 16:32:36 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	precision_s(char *par, int len_s)
{
	int	precision;
	int	i;

	i = 0;
	while (par[i])
	{
		if (par[i] == '.' && ft_isdigit(par[i + 1]))
		{
			precision = ft_atoi(par + ++i);
			if (precision > len_s)
				precision = len_s;
			return (precision);
		}
		++i;
	}
	precision = 0;
	return (precision);
}

void	ft_set_s(char **res, char *par, char *s, int field)
{
	int	len;
	int	i;
	int	j;

	len = ft_strlen(s);
	i = 0;
	j = 0;
	if (!ft_strchr(par, '-'))
	{
		while (i < field - len)
			res[0][i++] = ' ';
	}
	while (s[j] && i + j < field)
	{
		res[0][i + j] = s[j];
		++j;
	}
	if (ft_strchr(par, '-'))
	{
		while (i + j < field)
		{
			res[0][i + j] = ' ';
			++i;
		}
	}
}

void	print_null(char *par, int *ctr)
{
	int	field;
	int	i;

	field = 0;
	i = 0;
	read_field(&par, &field, 6, par[ft_strlen(par) - 1]);
	*ctr += field;
	if (ft_strchr(par, '-') && field)
		ft_putstr_fd("(null)", 1);
	while (i++ < field - 6)
		write (1, " ", 1);
	if (!ft_strchr(par, '-') && field)
		ft_putstr_fd("(null)", 1);
}

void	print_s(char *par, char *s, int *ctr)
{
	char	*res;
	int		len_s;
	int		field;

	if (s == NULL)
	{
		print_null(par, ctr);
		return ;
	}
	field = 0;
	len_s = ft_strlen(s);
	read_field(&par, &field, len_s, par[ft_strlen(par) - 1]);
	res = ft_calloc(field + 1, 1);
	if (!res)
		return ;
	*ctr += field;
	ft_set_s(&res, par, s, field);
	ft_print_result(res, field);
	free(res);
}
