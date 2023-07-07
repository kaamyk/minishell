/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:29:49 by xuluu             #+#    #+#             */
/*   Updated: 2022/11/09 12:30:55 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	length_dst;

	length_dst = ft_strlen(dst);
	i = 0;
	while (src[i] != '\0' && length_dst < n - 1)
	{
		dst[length_dst] = src[i];
		i++;
		length_dst++;
	}
	dst[length_dst] = '\0';
	return (dst);
}

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	length_dst;
	size_t	length_src;

	length_dst = ft_strlen(dst);
	length_src = ft_strlen(src);
	if (n < 1 || n < length_dst)
		return (n + length_src);
	else
	{
		if (n > length_dst)
			dst = ft_strncat(dst, src, n);
		return (length_dst + length_src);
	}
}
