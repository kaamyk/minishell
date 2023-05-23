/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:52:11 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/23 17:08:03 by anvincen         ###   ########.fr       */
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

void	ft_determine_command(char *command);

/*
ft_get_command.c
*/
void	ft_get_command(char *line);

void	ft_get_command2(char *line, char c);

/*
ft_command.c
*/
void	ft_check_dir(char *dir, int n);

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

#endif
