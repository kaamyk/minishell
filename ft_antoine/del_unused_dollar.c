/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_unused_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:39:16 by xuluu             #+#    #+#             */
/*   Updated: 2023/08/21 16:08:32 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_non_dollar_str(char *s, char *res, size_t *i)
{
	char	*sub_s;
	char	*tmp;
	size_t	len;

	len = (size_t)((s[0] == '$') & 1);
	(void) define_len(s, &len);
	if (len > 0)
	{
		sub_s = ft_substr(s, 0, len);
		if (sub_s == NULL)
			return (res);
		(*i) += len - 1;
		tmp = res;
		if (res == NULL)
			return (sub_s);
		else
			res = ft_strjoin(res, sub_s);
		free(sub_s);
		if (res == NULL)
			return (tmp);
		free(tmp);
	}
	return (res);
}

char	*del_dol_btwn_quotes(char *s, char *res, size_t *i)
{
	char	*sub_s;
	char	*tmp;
	size_t	len;
	char	c;

	len = 1;
	c = s[0];
	while (s[len] != c)
		++len;
	(*i) += (++len);
	sub_s = ft_substr(s, 0, len);
	tmp = res;
	if (res == NULL)
		res = sub_s;
	else
		res = ft_strjoin(res, sub_s);
	if (res == NULL)
		return (tmp);
	if (res != sub_s)
		free(sub_s);
	free(tmp);
	return (res);
}

char	*del_dol_without_quotes(char *s, char *res, size_t *i)
{
	char	*tmp;

	tmp = res;
	if (ft_strncmp(s, "$?", 2) == 0)
		(*i) += 1;
	if (res == NULL)
	{
		if (ft_strncmp(s, "$?", 2) == 0)
			res = ft_strdup("\'$?\'");
		else
			res = ft_strdup("$");
	}
	else
	{
		if (ft_strncmp(s, "$?", 2) == 0)
			res = ft_strjoin(res, "\'$?\'");
		else
			res = ft_strjoin(res, "$");
	}
	if (res == NULL)
		return (tmp);
	free(tmp);
	return (res);
}

char	*del_dollar(char *s, char *res, size_t *i)
{
	if (s[1] && (s[0] == '"' || s[0] == '\''))
		res = del_dol_btwn_quotes(s, res, i);
	else if (s[0] == '$')
	{
		(*i) += 1;
		res = del_dol_without_quotes(s, res, i);
	}
	return (res);
}

char	*del_unused_dollar(char	*s)
{
	char	*res;
	size_t	i;

	i = 0;
	res = NULL;
	if (s == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '$' && (s[i + 1]
				&& (s[i + 1] == '\'' || s[i + 1] == '"' || s[i + 1] == '$')))
			res = del_dollar(s + i + 1, res, &i);
		else
			res = get_non_dollar_str(s + i, res, &i);
		if (res == NULL)
			break ;
		++i;
	}
	free(s);
	return (res);
}
