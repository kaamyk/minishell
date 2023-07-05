/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:07 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/05 11:50:36 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_env;


// size_t	print_command(char *arg, t_data *data)
// {
// 	int		fd[2];
// 	int		pid;
// 	char	*cmd;
// 	char	*res;
// 	size_t	i;

// 	i = 0;
// 	while (arg[i] && arg[i] != ')')
// 		++i;
// 	cmd = malloc(i + 1);
// 	ft_strlcpy(cmd, (const char *)arg, i + 1);
// 	printf("cmd == %s\n", cmd);
// 	pipe(fd);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		data->print = false;
// 		close(fd[0]);
// 		ft_get_cmd(data, cmd);
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[1]);
// 		printf("%s", data->result);
// 		exit (0);
// 	}
// 	else
// 	{
// 		waitpid(pid, NULL, 0);
// 		res = join_print(fd);
// 		if (res != NULL)
// 			write(1, res, ft_strlen(res));
// 	}
// 	free(cmd);
// 	return (i + 3);
// }

size_t	print_quotes(char *arg, char c)
{
	size_t	i;

	i = 1;
	while (arg[i] && arg[i] != c)
	{
		if (arg[i] == '$' && arg[i + 1] != 0 && arg[i + 1] != ' '
			&& arg[i + 1] != '?' && ft_isalpha(arg[i + 1]) == 1)
			i += print_var(get_var_name(arg + i + 1)) + 1;
		else
			write(STDOUT_FILENO, &arg[i], 1);
		++i;
	}
	return (i);
}

char	*get_var_name(char *arg)
{
	char	*var;
	size_t	i;

	i = 0;
	while (ft_isalpha(arg[i]) == 1 || arg[i] == '_')
		++i;
	if (i == 0)
	{
		var = ft_calloc(1, 1);
		return (var);
	}
	var = malloc(i + 1);
	if (var == NULL)
		return (free_all(NULL, NULL, NULL));
	var[i--] = 0;
	while (1)
	{
		var[i] = arg[i];
		if (i == 0)
			break ;
		--i;
	}
	return (var);
}

bool	print_content(char *arg, t_data *data)
{
	size_t	i;

	i = 0;
	while (arg[i] != 0)
	{
		if (arg[i] == '"' || arg[i] == '\'')
			i += print_quotes(arg + i, arg[i]);
		else if (arg[i] == '$' && arg[i + 1] != 0 && arg[i + 1] != ' ')
		{
			if (arg[i + 1] == '?')
				printf("%d\n", data->exit_code);
			else
				i += print_var(get_var_name(arg + i + 1)) + 1;
		}
		else
		{
			write(1, arg + i, 1);
			++i;
		}
	}
	return (0);
}

bool	ft_echo(t_data *data)
{
	bool	nl;
	size_t	i;

	i = 0;
	if (data->arg == NULL || ft_strlen(data->arg) == 0)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (data->arg[i] == ' ')
		++i;
	nl = !(data->arg[0] == '-' && ft_strnstr(data->arg, "-n", 3) != NULL);
	if (nl == false)
		i += 2;
	print_content(data->arg + i, data);
	if (nl == true)
		printf("\n");
	return (0);
}
