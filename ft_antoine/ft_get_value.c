/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:30:55 by anvincen          #+#    #+#             */
/*   Updated: 2023/07/31 18:14:30 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_value(char **env, char *key)
{
	char	*var;
	char	*value;

	var = get_var(env, &key[0]);
	if (var == NULL)
		return (NULL);
	value = isolate_value(var);
	return (value);
}

char	*ft_del_quotes(char *s)
{
	char	*res;
	char	c;
	size_t	i;

	c = s[0];
	i = 0;
	if (s[i + 1])
		++i;
	while (s[i + 1] && s[i + 1] != c)
		++i;
	if (s[i + 1])
		res = ft_substr(s, 1, i);
	else
		res = NULL;
	return (res);
}
