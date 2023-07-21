/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:51:47 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/21 09:35:38 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H	
# define MINISHELL_H	

# include <stdio.h>
# include <stdint.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>

# include "../libft/libft.h"

typedef struct	s_data
{
	char	*cmd;
	char	*arg;
	bool	exit_code;
	char	**env;
}				t_data;

//	MAIN.C
bool	ft_strcmp(char *s1, char *s2);

//	ENV.C
bool	ft_env(t_data *data);

// 	EXPORT.C
bool	check_double(char **env, char *in_k, char *in_v);
char	**replace_value(char **env, char *o_var, char *n_var);
char	**add_variable(char **env, char *n_var);
char	**handle_inputs(char **env, char **inputs, bool *exit);
bool	ft_export(t_data *data);

//	ENVIRONMENT_UTILS.C
char	*check_export_inputs(char **l);
bool	print_env(char **env, bool a);
size_t	print_var(char **env, char *var);

//	ENVIRONMENT.C
char	**get_env_var_add(char **env, char **inputs);
char	*isolate_value(char *var);
char	*isolate_key(char *var);
char	**get_keys(char **env);
char	*get_var(char **env, char *var);

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
size_t	rank_char(char *s, char c);
size_t	count_char(char	*s, char c);
char	*del_char(char *s, char c);

//	UNSET.C
bool	input_valid(char **env, char *inpt_var);
char	**pop_unvalid_input(char **inputs, char *to_pop, size_t *l, bool *exit);
char	**check_inputs(char **env, char **inputs, size_t *len, bool *exit);
char	**delete_vars(char **env, char **inputs, size_t len);
bool	ft_unset(t_data *data);

//	FT_CD.C
bool	ft_cd(t_data *data);

//	PWD.C
bool	ft_pwd(void);

//	ECHO.C
bool	ft_echo(t_data *data);

#endif
