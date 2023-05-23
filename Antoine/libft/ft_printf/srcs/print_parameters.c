/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:03:43 by anvincen          #+#    #+#             */
/*   Updated: 2023/01/31 14:01:56 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_select_arg(char *par, char last_c, va_list arg_ptr, int *ctr)
{
	if (last_c == 'c')
		print_c(par, va_arg(arg_ptr, int), ctr);
	else if (last_c == 'd' || last_c == 'i')
		print_d(par, va_arg(arg_ptr, int), ctr);
	else if (last_c == 's')
		print_s(par, va_arg(arg_ptr, char *), ctr);
	else if (last_c == 'p')
		print_p(par, va_arg(arg_ptr, size_t), ctr);
	else if (last_c == 'x' || last_c == 'X')
		print_x(par, va_arg(arg_ptr, unsigned int), ctr);
	else if (last_c == 'o')
		print_o(par, va_arg(arg_ptr, unsigned int), ctr);
	else if (last_c == 'u')
		print_u(par, va_arg(arg_ptr, unsigned int), ctr);
	else if (last_c == '%')
		print_pc(ctr);
	(void)ctr;
	(void)arg_ptr;
	(void)par;
	return ;
}

void	ft_printpar(const char *s, int *start, va_list arg_ptr, int *ctr)
{
	char	last_c;
	char	*par;
	int		i;

	(void)arg_ptr;
	(void)ctr;
	(void)start;
	i = 1;
	while (s[i] && !ft_strchr("cdispxou%", s[i]))
		++i;
	par = malloc(i + 2);
	par[i + 1] = 0;
	last_c = s[i];
	*start += i + 1;
	while (i >= 0)
	{
		par[i] = s[i];
		i--;
	}
	ft_select_arg(par, last_c, arg_ptr, ctr);
	free(par);
}
