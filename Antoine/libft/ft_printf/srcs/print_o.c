/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_o.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:46:39 by anvincen          #+#    #+#             */
/*   Updated: 2023/01/25 17:19:36 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_nblen_oct(unsigned int n)
{
	int		len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		len++;
		n /= 8;
	}
	return (len);
}

void	ft_print_0_oct(char **res, char *par, size_t n, int field)
{
	int	len_n;
	int	i;

	len_n = ft_nblen_oct(n);
	i = 0;
	if (ft_strchr(par, '#') && n != 0)
		res[0][i++] = '0';
	while (i < field - len_n)
		res[0][i++] = '0';
	ft_putnbr_base_oct(n, res, len_n);
}

void	ft_print_nb_oct(char **res, char *par, size_t n, int field)
{
	int	len_n;
	int	i;

	len_n = ft_nblen_oct(n);
	i = 0;
	while (i < field - len_n)
		res[0][i++] = ' ';
	if (ft_strchr(par, '#') && n != 0)
		res[0][field - (len_n + 1)] = '0';
	ft_putnbr_base_oct(n, res, len_n);
}

void	ft_print_minus_oct(char **res, char *par, size_t n, int field)
{
	int	len_n;
	int	i;

	len_n = ft_nblen_oct(n);
	i = 0;
	if (ft_strchr(par, '#') && n != 0)
		res[0][i++] = '0';
	ft_putnbr_base_oct(n, res, len_n);
	i += len_n;
	while (i < field)
		res[0][i++] = ' ';
}

void	print_o(char *par, unsigned int n, int *ctr)
{
	char	*res;
	int		field;
	int		precision;

	field = 0;
	read_field(&par, &field, ft_nblen_oct(n), par[ft_strlen(par) - 1]);
	read_precision(par, &precision, &field, ft_nblen_oct(n));
	res = ft_calloc(field + 1, 1);
	if (!res)
		return ;
	*ctr += field;
	if (ft_strchr(par, '-'))
		ft_print_minus_oct(&res, par, n, field);
	else if (ft_strchr_str(par, "0.") && field <= precision)
		ft_print_0_oct(&res, par, n, field);
	else
		ft_print_nb_oct(&res, par, n, field);
	ft_print_result(res, field);
	free(res);
}
