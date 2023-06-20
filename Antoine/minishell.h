/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:52:11 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/26 11:18:10 by anvincen         ###   ########.fr       */
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

//dup2
# include<fcntl.h>

# include <stdbool.h>

# include "./libft/libft.h"

//wait
# include <sys/wait.h>

# define BUFFER_SIZE 1

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
	NO_SUCH,
}	t_error;

typedef struct s_syntaxe
{
	bool	doub;
	bool	open_q;
	bool	close_q;
}	t_syntaxe;

typedef struct s_quotes
{
	int	i;
	int	open_s;
	int	open_d;
}	t_quotes;

typedef struct s_split
{
	char	c;
	int		p;
	int		start;
}	t_split;

typedef struct s_redirec
{
	int			time;
	int			stop;
	char		*p1;
	char		*p2;
	char		*tmp;
	char		*string;
	char		*signe;
}	t_redirec;

typedef struct s_tab
{
	int		*tab_position;
	char	**tab_cmd;
	int		nb_cmd;
	int		nb_signe;
}	t_tab;

typedef struct s_data
{
	char	**tab_cmd;
	char	*str;
	char	*cmd;
	char	*arg;
	char	*result;
	bool	print;
	bool	double_input;
	bool	run;
}	t_data;

typedef struct	s_env
{
	char	**key;
	char	**value;
}				t_env;

/*
main.c
*/
char	*get_line(char *str);

/*
signal.c
*/
void	ft_signal(void);

/*
ft_split_cmd.c
*/
char	*ft_split_cmd(char *str);

char	*ft_add_string(char *s1, char *s2);

/*
ft_split_cmd2.c
*/
char	*ft_redirec(char *str);

/*
ft_split_cmd3.c
*/
char	*ft_redirec3(char *str);

void	ft_redirec4(t_quotes *quote, t_redirec *redirec, char *str);

/*
ft_check_syntaxe.c
*/
bool	ft_check_syntaxe(char *str);

/*
ft_error.c
*/
void	ft_error(t_error error, char *command, char *option);

/*
quotes.c
*/
bool	ft_check_open_quotes(char *line);

/*
ft_delete_space.c
*/
char	*ft_delete_space(char *str);

/*
ft_split_mn.c
*/
char	**ft_split_mn(char *str, char c);

/*
ft_split_mn2.c
*/
void	ft_check_quotes(t_quotes *quote, char *str, int i);

void	ft_get_value_quote(t_quotes *quote);

char	*ft_copy_str(char *str);

int		ft_count_len(char *str, int c);

void	free_tab_mn(char **tab);

/*
ft_parsing.c
*/
void	ft_parsing(char *str);

/*
ft_classify_str.c
*/
void	ft_classify_str(t_data *data, char *str);

char	*ft_classify_str2(char *str, char c);

void	ft_determine_command(t_data *data);

/*
ft_get_cmd.c
*/
void	ft_get_cmd(t_data *data, char *str);

/*
ft_split_cmd5.c
*/
void	ft_parsing6(t_tab *tab);

char	*ft_new_string(t_quotes *quote, char *str);

int		ft_without_quotes2(t_quotes *quote, t_tab *tab, char *str, int i);

/*
ft_redirection.c
*/
void	ft_redirection(t_data *data, char *arg1, char *arg2, bool input);

/*
ft_redirection2.c
*/
void	ft_redirection2(t_data *data, char *file);

/*
ft_redirection4.c
*/
char	*ft_creer_big_string(int time, char *string, char *line);

bool	ft_compare_str(char *s1, char *s2);

void	ft_redirection4(t_data *data, char *str);

/*
ft_other_cmd.c
*/
char	*ft_other_cmd2(char *cmd, bool check);

bool	ft_other_cmd(t_data *data);

char	*read_print2(t_data *data);

/*
ft_execute.c
*/
void	ft_free_all(t_data *data);

/****************************/

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
bool	ft_cd(char *arg);

size_t	nb_args(char *command);

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
//void	ft_env(void);
bool	ft_env(char *arg);

/*
export.c
*/
bool	add_variable(char **n_key, char **n_value);
bool	replace_value(char *n_value, size_t r);
bool	ft_export(char *arg);

/*
unset.c
*/
bool	input_valid(char *key, char *value, size_t len);
void	pop_unvalid_input(t_env *tmp, size_t r, size_t *len);
char	**delete_items(t_env *n_env, t_env *tmp, size_t lenunset);
void	ft_unset(char *arg);

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
echo.c
*/
bool	ft_echo(char *arg);

/*
join_print.c
*/
char	*join_print(int *fd);

char	*read_print(t_data *data, bool (*f)(char *));

#endif