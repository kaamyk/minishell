/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:30:55 by anvincen          #+#    #+#             */
/*   Updated: 2023/07/28 09:12:25 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*ft_get_value(char **env, char *key)
{
	char	*var;
	char	*value;

	var = get_var(env, key);
	if (var == NULL)
		return (NULL);
	value = isolate_value(key);
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

int	main(int ac, char **av, char **envp)
{
	char	**env;
	char	*value;
	char	*s;
	char	*tmp;

	(void)ac;
	(void)av;
	env = dup_list(envp);
	value = ft_get_value(env, "USER");
	printf("value USER = %s\n", value);
	free(value);
	value = ft_get_value(env, "UFT");
	printf("value UFT = %s\n", value);
	free(value);
	tmp = NULL;
	scanf("s with quotes : %s", tmp);
	s = ft_del_quotes(tmp);
	free(tmp);
	printf("s sans quotes = %s\n", s);
	return (0);
}
