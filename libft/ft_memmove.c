/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:29:49 by xuluu             #+#    #+#             */
/*   Updated: 2022/11/15 17:07:34 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_memmove2(char *dest, const char *src, size_t n)
{
	size_t	i;
	char	m;
	char	k;

	i = 0;
	while (i < n)
	{
		if (i > 0)
		{
			k = dest[i];
			dest[i] = m;
			m = k;
		}
		else
		{
			m = dest[i];
			dest[i] = src[i];
		}
		i++;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*str_dest;
	const char	*str_src;
	size_t		i;

	str_dest = dest;
	str_src = src;
	if ((str_src == NULL) && (str_dest == NULL))
		return (NULL);
	if (str_dest == str_src + 1)
		return (ft_memmove2(str_dest, str_src, n));
	i = 0;
	while (i < n)
	{
		str_dest[i] = str_src[i];
		i++;
	}
	return (str_dest);
}
