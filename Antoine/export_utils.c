/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/07 17:29:17 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env;

size_t	rank_char(char *s, char c)
{
	size_t	l;

	l = 0;
	while (s[l] && s[l] != c)
		++l;
	return (l);
}

size_t	count_char(char	*s, char c)
{
	size_t	n;
	size_t	i;

	n = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			++n;
		++i;
	}
	return (n);
}

char	*del_char(char *s, char c)
{
	char	*res;
	size_t	l;
	size_t	i;
	size_t	j;

	if (s == NULL)
		return (NULL);
	if (ft_strchr(s, c) == 0)
		return (s);
	l = ft_strlen(s) - count_char(s, c);
	res = malloc(sizeof(char) * (l + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && j < l)
	{
		if (s[i] != c)
			res[j++] = s[i];
		++i;
	}
	res[j] = 0;
	free(s);
	return (res);
}

// char	*join_quotes(char *s)
// {
// 	char	*res;

// 	if (s == NULL)
// 		return (NULL);
// 	res = malloc(ft_strlen(s) + 1);
// 	if (res == NULL)
// 		return (NULL);
// 	res = add_quotes(del_char(s, '"'));
// 	if (res == NULL)
// 		return (NULL);
// 	return (res);
// }

// char	*add_quotes(char *s)
// {
// 	char	*res;
// 	size_t	i;

// 	if (s == NULL)
// 		return (NULL);
// 	res = malloc(sizeof(char) * (ft_strlen(s) + (2 + 1)));
// 	if (res == NULL)
// 		return (NULL);
// 	i = 0;
// 	res[i++] = '"';
// 	while (s[i - 1])
// 	{
// 		res[i] = s[i - 1];
// 		++i;
// 	}
// 	res[i++] = '"';
// 	res[i] = 0;
// 	free(s);
// 	return (res);
// }
