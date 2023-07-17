/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:52:11 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/17 18:57:19 by anvincen         ###   ########.fr       */
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
# define PATH "/bin/"

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
	NOT_ACCESS,
}	t_error;

typedef struct s_env
{
	char	**key;
	char	**value;
	char	**env;
}				t_env;

typedef struct s_data
{
	char	**tab_cmd;
	char	*str;
	char	*file;
	char	*cmd;
	char	*arg;
	int		nb_cmd;
	int		exit_code;
	bool	print;
	bool	s_pipe;

	char	**tab_quotes;
	int		nb_quotes;
	char	*partie1;
	char	*partie2;

	char	**tab_cmd_logic;
	bool	*tab_logic;
	int		nb_logic;
	bool	s_bonus;

	char	**tab_wildcards;
	char	*str_with_wildcard;
	
	t_env	*s_env;
}	t_data;


/******************** ********************/
/*
main.c
*/
char	*take_input(char *str);

/*
signal.c
*/
void	ft_signal(void);

/******************** Check syntaxe ********************/
/*
ft_check_syntaxe.c
*/
bool	ft_check_syntaxe(t_data *data);
bool	ft_check_open_quotes(t_data *data);
bool	ft_check_syntax_inside(t_data *data, char *str);

/*
ft_run.c
*/
void	ft_execute_cmd(t_data *data);
void	ft_builtins(t_data *data);
void	ft_exit_code(t_data *data);

/******************** Parsing ********************/
/*
ft_parsing.c
*/
bool	ft_parsing(t_data *data);
char	**ft_create_tab_cmd(t_data *data, char *str);
char	*ft_read_string(t_data *data, char *str);
char	*ft_rewritten_strr2(char **tab, char *new_str, int i);

/*
ft_parsing2.c
*/
int		ft_check_quotes_in_str(char *str);
char	*ft_create_str_without_quotes(t_data *data, char *str);
char	*ft_create_string_summary(t_data *data, char *str);

/*
ft_parsing3.c
*/
char	*ft_parsing_mandatory_part2(t_data *data, char *str);

/*
ft_parsing4.c
*/
char	*ft_delete_horizontal_tab(char *str);

/*
ft_parsing5.c
*/
char	*ft_order_with_space(char *str);

/*
ft_parsing6.c
*/
char	*ft_tab_re(t_data *data, char *str);
char	**ft_create_tab_re(t_data *data, char *str);
char	*ft_add_semicolon(char *str);

/*
ft_parsing7.c
*/
char	*ft_put_cmd_at_first(t_data *data, char *str);

/*
ft_parsing8.c
*/
char	*ft_put_reout_at_first(t_data *data, char *str);

/*
ft_parsing9.c
*/
char	*ft_put_file_direction(char *str);

/******************** Redirections ********************/
/*
ft_redirection.c
*/
bool	ft_redirection_input(t_data *data, int i);
bool	ft_redirection_output(t_data *data, char *str);

/*
ft_redirection2.c
*/
char	*ft_redirection2(char *file);

/*
ft_redirection3.c
*/
char	*ft_redirection3(char *str);
char	*ft_creer_big_string(int time, char *string, char *line);

/******************** ********************/
/*
ft_get_cmd.c
*/
void	ft_get_cmd(t_data *data, char *str);

/*
ft_other_cmd.c
*/
void	ft_other_cmd(t_data *data);

/*
pipex.c
*/
void	ft_pipex(t_data *data);
void	execute(t_data *data);

/******************** Fonctions utiles ********************/
/*
ft_titre.c
*/
void	ft_titre(void);

/*
ft_error.c
*/
void	ft_error(t_error error, char *command, char *option);

/*
ft_delete_space.c
*/
char	*ft_delete_space(char *str);

/*
ft_split_mn.c
*/
char	**ft_split_mn(char *str, char c);

/*
ft_utile.c
*/
char	*ft_add_string(char *s1, char *s2);
char	*ft_copy_str(char *str);
void	ft_free_tab(char **tab);
void	ft_free_all(t_data *data);
void	ft_print_tab(char **tab);
bool	ft_compare_str(char *s1, char *s2);
int		ft_count_signe(char *str);
bool	ft_find_c(char *str, char c);
int		ft_nb_c(char *str, char c);
char	*ft_find_str(char *str);

/******************** Fonctions of Antoine ********************/

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
int		find_var_rank(t_env *env, char *key);
char	**init_keys(char **l, size_t len);
char	*isolate_value(char *s);
char	**init_values(char **l);
t_env	*init_env(char **env);

/*
environment_utils.c
*/
bool	input_valid(t_env *env, char *key, char *value, size_t len);
bool	check_double(t_env *env, char *key, char *value);
size_t	print_var(t_env *env, char *s);
bool	print_env(t_env *env, bool a);
char	*check_inputs(char **l);

/*
env.c
*/
bool	ft_env(t_data *data);

/*
export.c
*/
bool	add_variable(char **n_key, char **n_value, t_env *env, char **full_vl);
bool	replace_value(t_env *env, char *n_value, int r);
bool	ft_export(t_data *data);

/*
unset.c
*/
char	**delete_items(t_env *env, t_env *n_env, t_env *tmp, size_t len);
bool	ft_unset(t_env *env, char *arg);

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
void	*free_all(t_data *data, t_env *e, char **l, char *s);

/*
echo.c
*/
char	*get_var_name(char *arg);
bool	ft_echo(t_data *data);

/*
exit.c
*/
void	ft_exit(t_data *data);

/******************** Bonus ********************/
/*
ft_parsing_bonus.c
*/
void	ft_parsing_bonus(t_data *data, char *str);
int		ft_count_len_bonus(char *str);

/*
ft_execute_bonus.c
*/
void	ft_execute_bonus(t_data *data);

/*
ft_wildcards.c
*/
void	ft_wildcards(t_data *data, char *str);
bool	ft_find(char *s1, char *s2);

/*
ft_wildcards2.c
*/
char	*ft_get_current_file_directory(t_data *data, char *directorie);

/*
ft_wildcards3.c
*/
void	ft_start_with_wildcards(char *str, char *list_fd);

/*
ft_wildcards4.c
*/
char	*ft_one_wildcard(char *str);

/*
ft_find_center.c
*/
char	*ft_find_center(char *str, char *list_fd);
char	*ft_find_center_in_list(char *str, char *list_fd);

/*
ft_find_first.c
*/
char	*ft_find_first(char *str, char *list_fd);
char	*ft_find_first_in_list(char *str, char *list_fd);

/*
ft_find_end.c
*/
char	*ft_find_end(char *str, char *list_fd);
char	*ft_find_end_in_list(char *str, char *list_fd);

/*
ft_wildcards_is_center.c
*/
char	*ft_wildcards_is_center(char *str, char *list_fd);

#endif