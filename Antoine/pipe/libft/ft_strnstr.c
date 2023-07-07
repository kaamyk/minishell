/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:29:49 by xuluu             #+#    #+#             */
/*   Updated: 2022/11/21 10:59:37 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] != '\0')
	{
		j = 0;
		k = i;
		while ((j < len) && (little[j] != '0') && (big[k] == little[j]))
		{
			j++;
			k++;
			if (little[j] == 0 && k <= len)
				return ((char *)&big[i]);
		}
		i++;
	}
	return (0);
}
