/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:09:46 by anvincen          #+#    #+#             */
/*   Updated: 2023/01/25 10:47:49 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./struct.h"
# include "./libft.h"
# include <stdio.h>
# include <stdarg.h>

int		ft_printf(const char *s, ...) \
__attribute__ ((format(printf, 1, 2)));

//	LIBFT UTILS
int		ft_nblen(int nb);
int		ft_nblen_u(unsigned int n);

//	PRINTF UTILS
int		ft_strchr_str(char *s, char *to_find);
void	ft_elm_del(t_list *l_ptr, void (del)(void*));
t_list	*ft_lstcreate(char *content, int par);
void	ft_create_new_elm(t_list **l, char *s, int *end, int par);
t_list	*ft_create_list(char *s);
void	ft_print_result(char *res, int field);

//	DEBUG 
int		ft_debug(char *par);
int		ft_valid_combination(char *s, char last_c);
int		ft_check_point(char *par, char last_c);
int		ft_check_zero(char *par, char last_c);
int		ft_check_space(char *par, char last_c);
int		ft_check_minus(char *par);

//	PRINT PARAMETERS
void	set_n(char *res, int field, char *nb, int len_n);
void	ft_putnbr_base_hex(size_t n, char **res, int len_n, char *par);
void	ft_putnbr_base_oct(unsigned int n, char **res, int len_n);
int		ft_nblen_hex(size_t n);
void	ft_print_minus_hex(char **res, char *par, size_t n, int field);

void	ft_printpar(char *par, va_list arg_ptr, int *ctr);
void	print_d(char *par, int n, int *ctr);
void	print_s(char *par, char *s, int *ctr);
void	print_c(char *par, int c, int *ctr);
void	print_x(char *par, size_t n, int *ctr);
void	print_o(char *par, unsigned int n, int *ctr);
void	print_pc(int *ctr);
void	print_p(char *par, size_t n, int *ctr);
void	print_u(char *par, unsigned int n, int *ctr);

//	PRINT PARAMETERS UTILS
char	*ft_itoa_u(unsigned int n);

//	PRINT FLAGS
char	*set_0(char *res, int *field, int *n);
void	set_0_u(char *par, char **res, int field, size_t n);
void	set_space(char *res, char *par, int *field, int *n);
char	*set_space_u(char *res, char *par, int *field);
char	*set_plus(char *par, char *res, int field, int *n);
char	*set_plus_u(char *res);

//	DEFINE FIELD
void	read_precision(char *par, int *precision, int *field, int len);
void	read_field(char **par, int *field, int len_n, char last_c);
void	field_space(char *par, int *field, int n, int len_n);
void	field_point(char *par, int *field, int n, int len_n);

#endif