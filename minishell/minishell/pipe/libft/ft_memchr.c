/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:29:49 by xuluu             #+#    #+#             */
/*   Updated: 2022/11/21 10:43:23 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	if (n == 0)
		return (0);
	else if (c == 0)
		return ((unsigned char *)s);
	else
	{
		str = (unsigned char *)s;
		i = 0;
		while (i < n)
		{
			if (str[i] == (unsigned char)c)
				return ((unsigned char *)&str[i]);
			i++;
		}
		return (0);
	}
}
