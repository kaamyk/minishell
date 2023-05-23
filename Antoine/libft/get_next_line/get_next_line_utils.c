/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:49:02 by anvincen          #+#    #+#             */
/*   Updated: 2022/12/22 08:38:34 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_nlinstr(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 1;
	while (*s)
	{
		if (*s == '\n' || !*(s + 1))
			return (i);
		s++;
		i++;
	}
	return (i);
}

char	*ft_calloc_gnl(size_t nmemb, size_t size)
{
	char	*buf;
	size_t	i;

	i = 0;
	buf = NULL;
	if (!size || !nmemb)
	{
		buf = malloc(1);
		return (buf);
	}
	if (nmemb >= SIZE_MAX / size)
		return (buf);
	buf = malloc(nmemb * size);
	if (!buf)
		return (NULL);
	while (i < nmemb && ++i)
		buf[i - 1] = 0;
	return (buf);
}

int	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*l_ptr;
	t_list	*nextlst;

	if (!lst || !del)
		return (0);
	l_ptr = *lst;
	while (l_ptr)
	{
		nextlst = l_ptr->next;
		ft_lstdelone(l_ptr, free);
		l_ptr = nextlst;
	}
	*lst = NULL;
	return (1);
}

void	*ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst->content)
		del(lst->content);
	del(lst);
	return (NULL);
}

void	ft_assigne(t_list **l, t_list **n_elm, t_list **tmp, int n)
{
	if (!n)
	{
		(*l) = (*n_elm);
		(*tmp) = (*l);
	}
	else
	{
		(*l)->next = (*n_elm);
		(*l) = (*l)->next;
	}
}
