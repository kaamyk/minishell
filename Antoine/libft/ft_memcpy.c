/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 08:38:29 by anvincen          #+#    #+#             */
/*   Updated: 2023/05/28 21:53:50 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d_buf;
	const char	*s_buf;
	size_t		i;

	if (!dest && !src)
		return (NULL);
	d_buf = (char *) dest;
	s_buf = (const char *) src;
	i = 0;
	while (i < n)
	{
		d_buf[i] = s_buf[i];
		i++;
	}
	return (dest);
}
