/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:29:49 by xuluu             #+#    #+#             */
/*   Updated: 2022/11/08 12:07:59 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalnum(int character)
{
	if ((character > 64 && character < 91)
		|| (character > 96 && character < 123)
		|| (character > 47 && character < 58))
		return (character);
	else
		return (0);
}
