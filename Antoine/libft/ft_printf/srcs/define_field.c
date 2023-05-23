/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_field.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:03:43 by anvincen          #+#    #+#             */
/*   Updated: 2023/01/31 16:21:21 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_read_digit_field(char *par)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (par[i])
	{
		if (par[i] == '0')
			++i;
		if (par[i] == '.')
		{
			++i;
			while (ft_isdigit(par[i]))
				++i;
		}
		if (ft_isdigit(par[i]))
		{
			n = ft_atoi(par + i);
			while (ft_isdigit(par[i]))
				par[i++] = '1';
		}
	}
	return (n);
}

void	read_field(char *par, int *field, int len, char last_c)
{
	*field = ft_read_digit_field(par);
	if (*field < len)
		*field = len;
	if (ft_strchr(par, '#'))
	{
		if (*field <= len + 2)
			if (ft_strchr("xX", last_c))
				*field += 2;
		if (*field <= len + 1)
			if (last_c == 'o')
				*field += 1;
	}
}
