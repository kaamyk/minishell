/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:51:47 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/19 19:24:44 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "../libft/libft.h"

typedef struct	s_data
{
	char	*cmd;
	char	*arg;
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

//	ENVIRONMENT.C
char	*check_inputs(char **l);

//	ENVIRONMENT_UTILS.C
char	*isolate_value(char *var);
char	**get_values(char **env);
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

