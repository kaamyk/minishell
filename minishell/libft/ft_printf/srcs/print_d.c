/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:09:46 by anvincen          #+#    #+#             */
/*   Updated: 2023/01/25 17:19:27 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_define_field_d(int *field, char *par, int n, int len_n)
{
	read_field(&par, field, len_n, par[ft_strlen(par) - 1]);
	if (ft_strchr(par, '-'))
		if (*field < len_n)
			*field = len_n;
	if (ft_strchr_str(par, " +"))
	{
		field_space(par, field, n, len_n);
		return ;
	}
}

void	set_n(char *res, int field, char *nb, int len_n)
{
	int	i;

	i = 0;
	while (i < field && !res[i])
		res[i++] = ' ';
	i = 0;
	while (i <= len_n)
	{
		res[field - i] = nb[len_n - i];
		++i;
	}
	free(nb);
}

void	set_minus_d(char *res, char *nb, int field)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (res[i])
		++i;
	while (nb[j] && i < field)
	{
		res[i] = nb[j];
		++i;
		++j;
	}
	while (i < field)
		res[i++] = ' ';
	free(nb);
}

char	*ft_set_res(char *par, int *field, int n, int len_n)
{
	char	*res;
	int		precision;

	read_precision(par, &precision, field, len_n);
	res = NULL;
	res = ft_calloc(*field + 1, 1);
	if (!res)
		return (NULL);
	if (ft_strchr(par, '+'))
		res = set_plus(par, res, *field, &n);
	if (ft_strchr(par, '.'))
		if (*field <= precision)
			set_0(res, field, &n);
	if (ft_strchr(par, ' '))
		set_space(res, par, field, &n);
	if (ft_strchr(par, '-'))
		set_minus_d(res, ft_itoa(n), *field);
	else if (ft_strchr(par, '0'))
		set_0(res, field, &n);
	len_n = ft_nblen(n);
	if (!ft_strchr(par, '-'))
		set_n(res, *field, ft_itoa(n), len_n);
	return (res);
}

void	print_d(char *par, int n, int *ctr)
{
	char	*res;
	int		len_n;
	int		field;

	field = 0;
	len_n = ft_nblen(n);
	ft_define_field_d(&field, par, n, len_n);
	*ctr += field;
	res = ft_set_res(par, &field, n, len_n);
	ft_print_result(res, field);
	free(res);
}
