/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 10:33:51 by gcollet           #+#    #+#             */
/*   Updated: 2023/07/07 11:25:51 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char *argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	pipex(int argc, char **argv, char **envp, int *fd)
{
	int	i;

	i = 1;
	while (i < argc - 1)
		child_process(argv[i++], envp);
	dup2(fd[1], STDOUT_FILENO);
	execute(argv[argc - 1], envp);
}

char	*ft_delete_end_new_line(char *str)
{
	int		i;
	int		len;
	char	*new_str;

	if (!str)
		return (str);
	len = ft_strlen(str) - 1;
	while (len > 0 && str[len] == '\n')
		len--;
	len++;
	new_str = (char *)malloc((len + 1) * sizeof(char));
	if (!new_str)
		return (0);
	i = 0;
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = 0;
	free(str);
	return (new_str);
}

char	*ft_add_string(char *s1, char *s2)
{
	char	*tmp;

	tmp = s1;
	s1 = ft_strjoin(s1, s2);
	free(tmp);
	return (s1);
}

char	*join_print(int *fd)
{
	char	*res;
	char	*buffer;
	ssize_t	bytes;

	res = NULL;
	close(fd[1]);
	buffer = ft_calloc(1024, 1);
	while (1)
	{
		bytes = read(fd[0], buffer, 1);
		if (bytes <= 0)
			break ;
		if (res == NULL)
			res = ft_strdup(buffer);
		else
			res = ft_add_string(res, buffer);
	}
	free(buffer);
	close(fd[0]);
	res = ft_delete_end_new_line(res);
	return (res);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;
	int exit_code;
	char *str;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		pipex(argc, argv, envp, fd);
		close(fd[1]);
		exit(0);
	}
	else
	{
		str = join_print(fd);
		printf("[%s]\n", str);
		free(str);
		waitpid(pid, &exit_code, 0);
	}
	return (0);
}
