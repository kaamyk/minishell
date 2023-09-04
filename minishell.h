/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:52:11 by xuluu             #+#    #+#             */
/*   Updated: 2023/08/31 19:19:58 by anvincen         ###   ########.fr       */
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

# include <sys/ioctl.h>

# define BUFFER_SIZE 1
# define PATH "/bin/"

# define RED   "\x1B[31m"
# define GREEN "\x1b[32m"
# define KMAG  "\x1B[35m"
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

typedef struct s_data
{
	char	**tab_cmd;
	char	*str;
	char	*file;
	char	*cmd;
	char	*arg;
	int		nb_cmd;
	int		exit_code;

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

	bool	s_pipe;
	bool	s_infile;
	bool	s_outfile;

	char	*file_direction;
	int		id;

	char	*str_dollar;
	char	*str_quotes;
	int		i_quotes;

	char	**env;
}	t_data;

/******************** ********************/
/*
main.c
*/
char	*take_input(char *str);

/*
signal.c
*/
void	par_handler(int signum);
void	ignore_quit(void);
void	parent_signal(bool a);
void	chi_handler(int signum);
void	child_signal(void);

/******************** Check syntaxe ********************/
/*
ft_check_syntaxe.c
*/
bool	ft_check_syntaxe(t_data *data);
bool	ft_check_open_quotes(t_data *data);
bool	ft_check_syntax_inside(t_data *data, char *str);
bool	ft_check_syntax_inside2(t_data *data, char *str, int i);
bool	ft_check_space_string(char *str);
bool	ft_check_inside_quote(t_data *data);

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
char	**ft_change_file_direc(char **tab);

/******************** Redirections ********************/
/*
ft_redirection.c
*/
bool	ft_check_infile(t_data *data);
bool	ft_check_outfile(t_data *data);
void	ft_redirection_input(t_data *data, int i, int *fd, int tmp_fd);
void	ft_redirection_output(t_data *data, int i);
void	ft_sleep(int limiter);

/*
ft_redirection2.c
*/
char	*ft_redirection2(t_data *data, char *file);
char	*ft_find_limiter(char *str);

/*
ft_redirection3.c
*/
char	*ft_redirection3(t_data *data, char *str);
char	*ft_creer_big_string(char *string, char *line);

/******************** Run command ********************/
/*
ft_run.c
*/
void	ft_run_cmd(t_data *data);
void	ft_run(t_data *data, int i);

/*
ft_run_other_cmd.c
*/
void	ft_exit_code(t_data *data);
void	ft_other_cmd_without_pipe(t_data *data);
void	ft_other_cmd_with_pipe(t_data *data);
char	*find_path(char *cmd, char **envp);

/*
ft_run_with_pipe.c
*/
void	ft_run_cmd_with_pipe(t_data *data);

/*
ft_get_cmd.c
*/
void	ft_get_cmd(t_data *data, char *str);
char	*ft_cmd_with_path(char *str);
char	*ft_create_cmd(char *str, int i, int m, int *add);

/*
ft_builtins.c
*/
bool	ft_check_builtins(t_data *data);
void	ft_builtins(t_data *data, int id_cmd);

/*
ft_cmd_special.c
*/
void	ft_cmd_special(t_data *data);

/*
ft_signe_dollar.c
*/
void	ft_signe_dollar(t_data *data, int i);
void	ft_add_dollar(t_data *data, char *str, bool big);
int		ft_found_dollar(t_data *data, char *str);
char	*ft_character_to_string(char character);
int		ft_ignore(t_data *data, char *str);

/*
ft_signe_wave.c
*/
int		ft_check_signe_wave(t_data *data, char *str, int i);

/*
ft_print_error.c
*/
void	ft_check_exit_code(t_data *data, int i);

/******************** Fonctions utiles ********************/
/*
ft_titre.c
*/
void	ft_titre(void);

/*
ft_error.c
*/
void	ft_error(t_error error, char *command, char *option);
void	export_error(t_data *data, char *unvalid_var);

/*
ft_delete_space.c
*/
char	*ft_delete_space(char *str);

/*
ft_delete_quotes.c
*/
// void	ft_delete_quotes(char **tab);
char	*ft_delete_quotes(t_data *data, char *str);

/*
ft_split_mn.c
*/
char	**ft_split_mn(char *str, char c);

/*
ft_read_pipe.c
*/
char	*ft_read_pipe(int port_read);

/*
ft_utile.c
*/
char	*ft_add_string(char *s1, char *s2);
char	*ft_copy_str(char *str);
void	ft_free_tab(char **tab);
void	ft_free_all(t_data *data);
void	ft_free_tab_with_len(char **tab, int len);
bool	ft_compare_str(char *s1, char *s2);
int		ft_count_signe(char *str);
bool	ft_find_c(char *str, char c);
int		ft_nb_c(char *str, char c);
char	*ft_find_str(char *str);
void	ft_free_end(t_data *data);
char	*ft_get_str_without_space(char *str);

/******************** Fonctions of Antoine ********************/

//	ENV.C
bool	ft_env(t_data *data);

// 	EXPORT.C
bool	check_double(char **env, char *in_k, char *in_v);
char	**rpl_vl(char **env, char *o_var, char *n_var);
char	**add_variable(char **env, char *n_var);
char	**handle_inputs(t_data *data, char **env, char **inputs, bool *exit);
bool	ft_export(t_data *data);

// EXPORT_UTILS.C
bool	check_export_inputs(t_data *data, char *var);
char	**split_inputs(char *arg);

//	ENVIRONMENT_UTILS.C
bool	ft_ptr_inlist(char **l, char **ptr);
bool	ft_strcmp(char *s1, char *s2);
bool	print_env(char **env, bool a);
size_t	print_var(char **env, char *var);

//	ENVIRONMENT.C
char	**get_env_var_add(char **env, char **inputs);
char	*isolate_value(char *var);
char	*isolate_key(char *var);
char	**get_keys(char **env);
char	*get_var(char **env, char *var, bool e);

//	LIST.C
void	print_list(char **l);
size_t	len_list(char **l);
char	**dup_list(char **l);
bool	cpy_list(char **dest, char **src);
char	**join_list(char **lst1, char **lst2, size_t len_l1, size_t len_l2);

//	FREE.C
void	free_ptr(char *ptr);
void	free_list(char **lst);
//void	*free_all(t_data *data, t_env *e, char **l, char *s);

//	UTILS.C
size_t	define_len(char *s, size_t *len);
size_t	rank_char(char *s, char c);
size_t	count_char(char	*s, char c);
char	*del_char(char *s, char c);
bool	check_tab_double(char **tab, char *to_check);

//	UNSET.C
bool	input_valid(char **env, char *inpt_var);
char	**pop_unvalid_input(char **inputs, char *to_pop, size_t *l, bool *exit);
char	**check_inputs(char **env, char **inputs, size_t *len, bool *exit);
char	**delete_vars(char **env, char **inputs, size_t len);
bool	ft_unset(t_data *data);

//	FT_CD.C
bool	ft_cd(t_data *data);
char	*get_complete_path(char **env, char *arg, int *exit);

//	FT_CD_UTILS.C
void	update_pwd(t_data *data, int *exit);
bool	update_oldpwd(t_data *data, int *exit);

//	PWD.C
bool	ft_pwd(t_data *data);

//	ECHO.C
bool	ft_echo(t_data *data);

/*
exit.c
*/
void	ft_exit(t_data *data);

/*
ft_get_value.c
*/
char	*ft_get_value(char **env, char *key);
char	*ft_del_quotes(char *s);

/*
del_unused_dollar.c
*/
char	*del_unused_dollar(char	*s);

/******************** Bonus ********************/
/*
ft_parsing_bonus.c
*/
void	ft_parsing_bonus(t_data *data, char *str);
int		ft_count_len_bonus(char *str);

/*
ft_run_bonus.c
*/
void	ft_run_bonus(t_data *data);

/*
ft_wildcards.c
*/
char	*ft_wildcards(t_data *data, char *str);
bool	ft_find(char *s1, char *s2);

/*
ft_wildcards2.c
*/
char	*ft_get_current_directory(t_data *data);

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