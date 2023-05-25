/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:30:55 by anvincen          #+#    #+#             */
/*   Updated: 2023/05/25 15:12:56 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include <signal.h>
# include <sys/types.h>

//get command
# include <readline/readline.h>
# include <readline/history.h>

//ls
#include <dirent.h>
#include <errno.h>

# include <stdbool.h>

# include "./libft/libft.h"

# define RED   "\x1B[31m"
# define GREEN "\x1b[32m"
# define RESET "\x1B[0m"

typedef struct sigaction	t_sig;
typedef enum s_error
{
	SYNTAXE,
	NOT_FOUND,
	DIRECTORY,
	NOT_VALID,
}	t_error;

void	ft_determine_command(char **command);

char	*get_line(char *str);

/*
ft_get_command.c
*/
void	ft_get_command(char *line);

void	ft_get_command2(char *line, char c);

/*
ft_command.c
*/
void	ft_pwd();
void	ft_read_dir(DIR *dp);
void	ft_check_dir(char *dir, int n);
int		ft_builtins(char **command);
int		ft_redirections(char *command);
void	ft_determine_command(char **command);


/*
ft_error.c
*/
void	ft_error(t_error error, char *command, char *option);

/*
signal.c
*/
void	ignore_quit(void);
void	sig_handler(int signum);
void	ft_signal(void);

/*
quotes.c
*/
char	*ft_check_open_quotes(char **command);
char	*ft_quotes(char **line);
/*
change_directory.c
*/
void	ft_cd(char **command);
size_t	nb_args(char **command);

#endif

