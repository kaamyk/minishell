/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:46:39 by anvincen          #+#    #+#             */
/*   Updated: 2023/01/25 09:22:34 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#define BASE "0123456789abcdef"

void	ft_print_nb(char **res, char *par, size_t n, int field)
{
	int	len_n;
	int	i;

	len_n = ft_nblen_hex(n);
	i = 0;
	while (i < field - len_n - 2)
		res[0][i++] = ' ';
	if (n != 0)
	{
		res[0][i++] = '0';
		res[0][i++] = 'x';
	}
	ft_putnbr_base_hex(n, res, len_n, par);
}

void	ft_print_minus(char **res, char *par, size_t n, int field)
{
	int		len_n;
	int		i;

	len_n = ft_nblen_hex(n);
	i = 0;
	res[0][i++] = '0';
	res[0][i++] = 'x';
	ft_putnbr_base_hex(n, res, len_n, par);
	i += len_n;
	while (i < field)
		res[0][i++] = ' ';
}

void	adapt_field(char *par, int *field)
{
	int	atoi;
	int	i;

	atoi = 0;
	i = 0;
	while (par[i])
	{
		if (ft_isdigit(par[i]))
		{
			atoi = ft_atoi(par + i);
			if (atoi <= 5)
				*field = 5;
			else
				*field = atoi;
			return ;
		}
		++i;
	}
	*field = 5;
}

void	print_nil(char *par, int *ctr)
{
	int	field;
	int	i;

	field = 0;
	i = 0;
	adapt_field(par, &field);
	*ctr += field;
	if (ft_strchr(par, '-'))
		ft_putstr_fd("(nil)", 1);
	while (i++ < field - 5)
		write (1, " ", 1);
	if (!ft_strchr(par, '-'))
		ft_putstr_fd("(nil)", 1);
}

void	print_p(char *par, size_t n, int *ctr)
{
	char	*res;
	int		field;

	field = 0;
	if (n != 0)
	{
		read_field(&par, &field, ft_nblen_hex(n), par[ft_strlen(par) - 1]);
		res = ft_calloc(field + 1, 1);
	}
	else
	{
		print_nil(par, ctr);
		return ;
	}
	*ctr += field;
	if (ft_strchr(par, '-'))
		ft_print_minus(&res, par, n, field);
	else
		ft_print_nb(&res, par, n, field);
	ft_print_result(res, field);
	free(res);
}
