/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:30:55 by anvincen          #+#    #+#             */
/*   Updated: 2023/06/07 18:42:06 by antoine          ###   ########.fr       */
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

typedef struct	s_env
{
	//char	**env;
	char	**key;
	char	**value;
	int		len;
}				t_env;

void	ft_determine_command(char *command);

char	*get_line(char *str);

/*
main.c
*/
t_env	*init_env(char **env);

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
bool	ft_builtins(char *command);
int		ft_redirections(char *command);
void	ft_determine_command(char *line);

/*
free.c
*/
void	free_list(void **lst);
void	free_ptr(void *ptr);

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
bool	ft_check_open_quotes(char *command);
bool	ft_quotes(char *line);

/*
list.c
*/
void	print_list(char **l);
size_t	len_list(char **l);
char	**dup_list(char **l);
bool	cpy_list(char **l_dest, char **l_src);
char	**join_list(char **lst1, char **lst2);

/*
change_directory.c
*/
void	ft_cd(char *command, const char *arg);
size_t	nb_args(char *command);

/*
echo.c
*/
void	ft_echo(char *command, char *arg);

/*
env.c
*/
size_t	print_var(char *s);
void	print_env(void);

/*
env_utils.c
*/
char	**init_keys(char **l, size_t len);
char	**init_values(char **l);
int		find_var_rank(char *key);
bool	check_double(char *key, char *value);

/*
export.c
*/
void	add_variable(char **n_key, char **n_value);
char	*isolate_value(char *s);
void	replace_value(char *n_value, size_t r);
void	ft_export(char *command, char *arg);

/*
unset.c
*/
char	**isolate_keys(char **inputs, size_t l_inputs);
int		*find_ranks(char **inputs, size_t l_inputs);
char	**delete_items_list(int *ranks);
char	**ft_unset(char *command, char *arg);


/*
export_utils.c
*/
size_t	rank_char(char *s, char c);
size_t	count_char(char	*s, char c);
char	*del_char(char *s, char c);
char	*join_quotes(char *s);

#endif

