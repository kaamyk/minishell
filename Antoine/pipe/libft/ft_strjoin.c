/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:22:08 by xuluu             #+#    #+#             */
/*   Updated: 2022/11/15 17:37:49 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	m;
	size_t	len_str;

	len_str = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc((len_str + 1) * sizeof(char));
	if (!str)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	m = 0;
	while (s2[m] != '\0')
	{
		str[i] = s2[m];
		i++;
		m++;
	}
	str[i] = '\0';
	return (str);
}
