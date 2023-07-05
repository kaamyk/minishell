/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:22:08 by xuluu             #+#    #+#             */
/*   Updated: 2022/11/12 17:22:44 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	check_set(char const *s1, size_t i, char const *set)
{
	size_t	m;

	m = 0;
	while (set[m] != 0)
	{
		if (s1[i] == set[m])
			return (1);
		m++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	start;
	size_t	end;

	start = 0;
	while (check_set(s1, start, set) == 1)
		start++;
	end = ft_strlen(s1);
	while (end > start && check_set(s1, (end - 1), set))
		end--;
	str = (char *)malloc(((end - start) + 1) * sizeof(char));
	if (!str)
		return (0);
	i = 0;
	while (start < end)
	{
		str[i] = s1[start];
		i++;
		start++;
	}
	str[i] = 0;
	return (str);
}
