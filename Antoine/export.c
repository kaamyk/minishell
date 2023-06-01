/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/01 13:52:55 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**g_env;

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

	if (ft_strchr(s, c) == 0)
		return (s);
	l = ft_strlen(s) - count_char(s, c);
	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (s[i] && j < l)
	{
		if (s[i] == c)
		{
			res[j] = s[i];
			++j;
		}
		++i;
	}
	res[j] = 0;
	return (s);
}

char	*isolate_value(char *s)
{
	char	*res;
	size_t	len;
	size_t	rank_sep;

	res = NULL;
	rank_sep = rank_char(s, '=');
	len = ft_strlen(s) - rank_sep;
	res = malloc(len + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (s[i + rank_sep] && i < len)
	{
		res[i] = s[rank_sep + i];
		++i;
	}
	res[i] = 0;
	return (res);
}

char	*join_quotes(char *s)
{
	char	*res;
	char	*tmp;
	size_t	i;

	i = 0;
	tmp = res;
	res = isolate_value(s);
	if (res == NULL)
		return (NULL);
	free(tmp);
	printf("Apres isolate => res == %s\n", res);
	tmp = res;
	res = del_char(res, '"');
	if (res == NULL)
		return (NULL);
	free(tmp);
	return (res);
}

char	**format_env(char **inputs)
{
	char	*tmp;
	size_t	i;

	res = NULL;
	i = 0;
	while (inputs[i])
	{
		tmp = inputs[i];
		if (ft_strchr(inputs[i], '=') == 0)
			inputs[i] = ft_strjoin(inputs[i], "=''");
		else if (ft_strchr(inputs[i], '"') == 0 || ft_strchr(inputs[i], '\'') == 0)
			inputs[i] = join_quotes(inputs[i] + (ft_strchr(inputs[i], '=') - inputs[i]), false);
		if (tmp != NULL)
			free(tmp);
		++i;
	}
	return (inputs);
}

void	ft_export(char *command, char *arg)
{
	char	**inputs;
	char	**n_env;
	char	**tmp;

	(void) command;
	if (arg == NULL)
	{
		printf("Dans le else print_list\n");
		print_list(g_env);
		return ;
	}
	inputs = format_env(ft_split(arg, ' '));
	n_env = join_list(g_env, inputs);
	free_list((void **) inputs);
	if (n_env == NULL)
		return ;
	tmp = g_env;
	g_env = n_env;
	free_list((void **)tmp);
}

// int	main(int argc, char **argv, char **env)
// {
// 	char	*s;

// 	(void) argc;
// 	(void) argv;
// 	g_env = dup_list(env);
// 	if (g_env == NULL)
// 	{
// 		printf("allocation failed");
// 		exit (errno);
// 	}
// 	while (1)
// 	{
// 		s = readline("$>");
// 		if (s == NULL)
// 		{
// 			free_list((void **) g_env);
// 			return (0);
// 		}
// 		printf("comp == %d\n", strncmp(s, "ehco", strlen("echo")));
// 		// if (strcmp(s, "pwd") == 0)
// 		// 	ft_pwd();
// 		// if (strcmp(s, "cd") == 0)
// 		// 	ft_cd("cd", NULL);
// 		// else if (strncmp(s, "cd", 2) == 0)
// 		// 	ft_cd("cd", s + 3);
// 		if (strncmp(s, "export ", strlen("export ")) == 0)
// 			ft_export("export", s + strlen("export "));
// 		else if (strncmp(s, "export", strlen("export")) == 0)
// 			ft_export("export", NULL);
// 		else if (strncmp(s, "echo", strlen("echo")))
// 			ft_echo("echo", s + strlen("echo"));
// 	}
// 	return (0);
// }
