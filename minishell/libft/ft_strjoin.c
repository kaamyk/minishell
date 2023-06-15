/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:45:14 by anvincen          #+#    #+#             */
/*   Updated: 2023/06/01 09:40:45 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		t_len;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	t_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = malloc(sizeof(char) * t_len);
	if (!result)
		return (NULL);
	i = 0;
	while (*s1)
	{
		result[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		result[i] = *s2;
		s2++;
		i++;
	}
	result[i] = 0;
	return (result);
}
