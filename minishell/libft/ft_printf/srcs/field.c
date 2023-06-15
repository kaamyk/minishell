/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:09:46 by anvincen          #+#    #+#             */
/*   Updated: 2023/01/25 15:48:08 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	read_precision(char *par, int *precision, int *field, int len)
{
	int	i;
	int	last_c;

	*precision = 0;
	i = 0;
	last_c = par[ft_strlen(par) - 1];
	while (par[i])
	{
		if (par[i] == '.')
			if (ft_isdigit(par[++i]))
				*precision = ft_atoi(par + i);
		++i;
	}
	if (last_c != 's')
		if (*precision < len)
			*precision = len;
	if (ft_strchr(par, '#'))
	{
		if (ft_strchr("Xx", last_c))
			*precision += 2;
		else if (last_c == 'o' && *precision <= len)
			*precision += 1;
	}
	if (*field < *precision)
		*field = *precision;
}

void	define_field(int *field, int len, char *par, char last_c)
{
	if (*field < len)
		*field = len;
	if (*field <= len + 2)
		if (last_c == 'p' || (ft_strchr(par, '#') && ft_strchr("xX", last_c)))
			*field = len + 2;
}

void	read_field(char **par, int *field, int len, char last_c)
{
	int	precision;
	int	i;

	if (last_c == 's' && ft_strchr(*par, '.'))
		read_precision(*par, &precision, field, len);
	i = 0;
	while (par[0][i] && !*field)
	{
		if (par[0][i] == '0')
			++i;
		if (ft_isdigit(par[0][i]))
		{
			*field = ft_atoi(*par + i);
			if (last_c != 's')
				while (ft_isdigit(par[0][i]))
					par[0][i++] = '1';
		}
		++i;
	}
	if (last_c != 's' || !ft_strchr(*par, '.'))
		define_field(field, len, *par, last_c);
}

void	field_space(char *par, int *field, int n, int len_n)
{
	if (*field < len_n)
		*field = len_n;
	else if ((*field == len_n && n > 0) || ft_strchr_str(par, "."))
		++(*field);
}

void	field_point(char *par, int *field, int n, int len_n)
{
	(void)n;
	if (ft_strchr_str(par, " +") && *field <= len_n)
		++(*field);
}
