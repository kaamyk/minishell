/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:03:43 by anvincen          #+#    #+#             */
/*   Updated: 2023/01/25 17:18:31 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	print_pc(int *ctr)
{
	char	*res;

	res = ft_calloc(2, 1);
	res[0] = '%';
	*ctr += 1;
	ft_print_result(res, 1);
	free(res);
}
