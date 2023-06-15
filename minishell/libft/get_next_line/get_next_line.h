/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 10:45:12 by anvincen          #+#    #+#             */
/*   Updated: 2022/12/22 08:56:03 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
void	ft_assigne(t_list **l, t_list **n_elm, t_list **tmp, int n);
char	*ft_calloc_gnl(size_t nmemb, size_t size);
char	*ft_cpylst(t_list *lst, int mult, int lastlen);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstclear(t_list **lst, void (*del)(void *));
void	*ft_lstdelone(t_list *lst, void (*del)(void*));
int		ft_lstnew(t_list **l, int fd);
char	*ft_readfile(int fd);
int		ft_strlen(char *s);
int		ft_nlinstr(char *s);

#endif