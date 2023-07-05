/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:11:11 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/19 17:14:14 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	int result;
	
	if (ac == 2)
	{
		//result = access(av[1], F_OK);
		result = access(av[1], R_OK);
		printf("%d\n", result);
	}
}
