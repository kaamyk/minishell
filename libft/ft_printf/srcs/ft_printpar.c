/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printpar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:09:46 by anvincen          #+#    #+#             */
/*   Updated: 2023/01/25 14:47:42 by antoine          ###   ########.fr       */
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
	return ;
}

void	ft_printpar(char *par, va_list arg_ptr, int *ctr)
{
	char	last_c;
	int		i;

	i = 1;
	while (par[i + 1])
		i++;
	last_c = par[i];
	ft_select_arg(par, last_c, arg_ptr, ctr);
}
