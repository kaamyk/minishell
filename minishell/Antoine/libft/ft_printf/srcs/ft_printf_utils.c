/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:03:43 by anvincen          #+#    #+#             */
/*   Updated: 2023/02/06 16:37:46 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_elm_del(t_list *l_ptr, void (del)(void*))
{
	if (!l_ptr || !del)
		return ;
	del(l_ptr->content);
	del(l_ptr->result);
	del(l_ptr);
}

t_list	*ft_lstcreate(char *content, int par)
{
	t_list	*n_elm;

	n_elm = malloc (sizeof(t_list));
	if (!n_elm)
		return (NULL);
	n_elm->content = content;
	n_elm->result = NULL;
	n_elm->par = par;
	n_elm->next = NULL;
	return (n_elm);
}

void	ft_end_par(char *s, int *end, int par)
{
	if (!par)
		while (s[*end] && s[*end] != '%' && ++(*end))
			;
	else
	{
		while (s[*end] && !ft_strchr("cspdiuoxX%", s[*end]))
			++(*end);
		++(*end);
	}
}

void	ft_create_new_elm(t_list **l, char *s, int *end, int par)
{
	char	*tmp;
	int		start;
	int		i;

	start = (*end)++;
	ft_end_par(s, end, par);
	tmp = ft_calloc(*end - start + 2, 1);
	i = 0;
	while (i < *end - start && ++i)
		tmp[i - 1] = s[(i - 1) + start];
	ft_lstadd_back(l, ft_lstcreate(tmp, par));
}

t_list	*ft_create_list(char *s)
{
	t_list	*l;
	int		i;

	l = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] != '%')
			ft_create_new_elm(&l, s, &i, 0);
		else
			ft_create_new_elm(&l, s, &i, 1);
	}
	return (l);
}
