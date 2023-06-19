/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:30:55 by anvincen          #+#    #+#             */
/*   Updated: 2023/06/19 16:41:10 by antoine          ###   ########.fr       */
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
# include <dirent.h>
# include <errno.h>

# include <stdbool.h>
# include <sys/wait.h>
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
	char	**key;
	char	**value;
}				t_env;

typedef struct	s_data
{
	char	*cmd;
	char	*arg;
	bool	print;
}				t_data;

void	ft_determine_command(char *command);

char	*get_line(char *str);

/*
main.c
*/
char	*get_line(char *str);
void	ft_read_line(char *line);

/*
utils.c
*/
size_t	rank_char(char *s, char c);
size_t	count_char(char	*s, char c);
char	*del_char(char *s, char c);

/*
free.c
*/
void	free_ptr(char *ptr);
void	free_list(char **lst, size_t len);
void	free_env(t_env *env);
void	*free_all(t_env *e, char **l, char *s);

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
bool	cpy_list(char **dest, char **src, size_t l_src);
char	**join_list(char **lst1, char **lst2, size_t len_l1, size_t len_l2);

/*
change_directory.c
*/
void	ft_cd(char *command, const char *arg);
size_t	nb_args(char *command);

/*
echo.c
*/
bool	ft_echo(char *arg);

/*
environment.c
*/
char	**init_keys(char **l, size_t len);
char	*isolate_value(char *s);
char	**init_values(char **l);
t_env	*init_env(char **env);

/*
environment_utils.c
*/
bool	check_double(char *key, char *value);
int		find_var_rank(char *key);
size_t	print_var(char *s);
bool	print_env(bool a);
char	*check_inputs(char **l);

/*
env.c
*/
void	ft_env(void);

/*
export.c
*/
bool	add_variable(char **n_key, char **n_value);
bool	replace_value(char *n_value, size_t r);
bool	handle_inputs(t_env *res);
bool	ft_export(char *arg);

/*
unset.c
*/
bool	input_valid(char *key, char *value, size_t len);
void	pop_unvalid_input(t_env *tmp, size_t r, size_t *len);
char	**delete_items(t_env *n_env, t_env *tmp, size_t lenunset);
void	ft_unset(char *arg);

/*
read_print
*/
char	*join_print(int *fd);
char	*read_print(bool(*f)(char *), char *arg, bool print);

#endif

