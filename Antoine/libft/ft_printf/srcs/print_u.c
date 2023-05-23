/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:09:46 by anvincen          #+#    #+#             */
/*   Updated: 2023/01/25 17:18:17 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_nblen_u(unsigned int n)
{
	int		len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

void	ft_define_field_d_u(int *field, char *par, unsigned int n, int len_n)
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

void	set_n_u(char *res, int field, char *nb, int len_n)
{
	int	i;

	i = 1;
	while (i <= len_n)
	{
		res[field - i] = nb[len_n - i];
		++i;
	}
	free(nb);
}

char	*ft_set_res_u(char *par, int *field, unsigned int n, int len_n)
{
	char	*res;
	int		precision;

	res = NULL;
	read_precision(par, &precision, field, ft_nblen_u(n));
	res = ft_calloc(*field + 1, 1);
	if (!res)
		return (NULL);
	if (ft_strchr(par, '+'))
		res = set_plus_u(res);
	if (ft_strchr(par, '-'))
		set_n_u(res, len_n, ft_itoa_u(n), len_n);
	if ((ft_strchr(par, ' ') && !ft_strchr(par, '+'))
		|| ft_strchr(par, '-'))
		res = set_space_u(res, par, field);
	if (ft_strchr_str(par, "0.") && *field <= precision)
		set_0_u(par, &res, *field, n);
	len_n = ft_nblen_u(n);
	if (!ft_strchr(par, '-'))
	{
		set_n_u(res, *field, ft_itoa_u(n), len_n);
		set_space_u(res, par, field);
	}
	return (res);
}

void	print_u(char *par, unsigned int n, int *ctr)
{
	char	*res;
	int		len_n;
	int		field;

	field = 0;
	len_n = ft_nblen_u(n);
	ft_define_field_d_u(&field, par, n, len_n);
	res = ft_set_res_u(par, &field, n, len_n);
	if (!res)
		return ;
	*ctr += field;
	ft_print_result(res, field);
	free(res);
}
