/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:29:49 by xuluu             #+#    #+#             */
/*   Updated: 2022/11/23 17:58:10 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	f;

	if (c == 0)
		return ((char *)&s[ft_strlen(s)]);
	i = ft_strlen(s);
	f = 0;
	while (i > 0)
	{
		if (s[i] == c)
		{
			f++;
			return ((char *)&s[i]);
		}
		i--;
	}
	if ((f == 0 && s[i] == c) || (c > 127))
		return ((char *)&s[i]);
	return (0);
}
