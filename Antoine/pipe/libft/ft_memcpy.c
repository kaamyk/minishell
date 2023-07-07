/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:29:49 by xuluu             #+#    #+#             */
/*   Updated: 2022/11/08 17:24:15 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*str_src;
	char		*str_dest;
	size_t		i;

	str_src = src;
	str_dest = dest;
	if ((str_src == NULL) && (str_dest == NULL))
		return (NULL);
	else
	{
		i = 0;
		while (i < n)
		{
			str_dest[i] = str_src[i];
			i++;
		}
	}
	return (str_dest);
}
