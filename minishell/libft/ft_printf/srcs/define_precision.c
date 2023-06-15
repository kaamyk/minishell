/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:03:43 by anvincen          #+#    #+#             */
/*   Updated: 2023/01/31 16:20:25 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_read_digit_precision(char *par)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (par[i] && par[i] != '.')
		++i;
	n = ft_atoi(par + i + 1);
	while (ft_isdigit(par[i]))
		par[i++] = '1';
	return (n);
}

void	ft_read_precision(char *par, int *precision, int len, char last_c)
{
	*precision = ft_read_digit_precision(par);
	if (*precision < len && last_c != 's')
	{
		*precision = len;
		if (ft_strchr(par, '#'))
		{
			if (*precision <= len + 2 && ft_strchr("xX", last_c))
				*precision += 2;
			else if (*precision <= len + 1 && last_c == 'o')
				*precision += 1;
		}
	}
}
