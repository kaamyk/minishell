/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_xX.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:46:39 by anvincen          #+#    #+#             */
/*   Updated: 2023/01/25 15:56:51 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_print_0_hex(char **res, char *par, size_t n, int field)
{
	int	len_n;
	int	i;

	len_n = ft_nblen_hex(n);
	i = 0;
	if (ft_strchr(par, '#') && n != 0)
	{
		res[0][i++] = '0';
		res[0][i++] = par[ft_strlen(par) - 1];
	}
	while (i < field - len_n)
		res[0][i++] = '0';
	ft_putnbr_base_hex(n, res, len_n, par);
}

void	ft_print_nb_hex(char **res, char *par, size_t n, int field)
{
	int	len_n;
	int	i;

	len_n = ft_nblen_hex(n);
	i = 0;
	while (i < field - len_n)
		res[0][i++] = ' ';
	if (n != 0 && ft_strchr(par, '#'))
	{
		res[0][field - (len_n + 2)] = '0';
		res[0][field - (len_n + 1)] = par[ft_strlen(par) - 1];
	}
	ft_putnbr_base_hex(n, res, len_n, par);
}

void	ft_print_minus_hex(char **res, char *par, size_t n, int field)
{
	int	len_n;
	int	i;

	len_n = ft_nblen_hex(n);
	i = 0;
	if (ft_strchr(par, '#') && n != 0)
	{
		res[0][i++] = '0';
		res[0][i++] = par[ft_strlen(par) - 1];
	}
	ft_putnbr_base_hex(n, res, len_n, par);
	i += len_n;
	while (i < field)
		res[0][i++] = ' ';
}

void	print_x(char *par, size_t n, int *ctr)
{
	char	*res;
	int		field;
	int		precision;
	char	last_c;

	field = 0;
	last_c = par[ft_strlen(par) - 1];
	read_field(&par, &field, ft_nblen_hex(n), last_c);
	read_precision(par, &precision, &field, ft_nblen_hex(n));
	if (n == 0 && field == 3)
		field -= 2;
	res = ft_calloc(field + 1, 1);
	if (!res)
		return ;
	*ctr += field;
	if (ft_strchr(par, '-'))
		ft_print_minus_hex(&res, par, n, field);
	else if (ft_strchr_str(par, "0.") && field <= precision)
		ft_print_0_hex(&res, par, n, field);
	else
		ft_print_nb_hex(&res, par, n, field);
	ft_print_result(res, field);
	free(res);
}
