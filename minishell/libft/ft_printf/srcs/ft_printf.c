/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:09:46 by anvincen          #+#    #+#             */
/*   Updated: 2023/02/06 11:42:07 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/ft_printf.h"

void	ft_print_result(char *res, int field)
{
	int	i;

	i = 0;
	while (i < field)
	{
		write (1, &res[i], 1);
		++i;
	}
}

void	ft_print_content(char *content, int *ctr)
{
	ft_putstr_fd(content, 1);
	*ctr += ft_strlen(content);
	if (content == NULL)
		++(*ctr);
}

/*int	ft_printlst(t_list *l)
{
	t_list	*tmp;
	int		ctr;

	ctr = 0;
	while (l)
	{
		if (l->result)
			ft_print_result(l->result, l->content, &ctr);
		else
			ft_print_content(l->content, &ctr);
		tmp = l;
		l = l->next;
		if (tmp->content != NULL)
			ft_elm_del(tmp, free);
	}
	return (ctr);
}*/

int	ft_printf(const char *s, ...)
{
	int		ctr;
	t_list	*l;
	t_list	*tmp;
	va_list	arg_ptr;

	ctr = 0;
	l = ft_create_list((char *)s);
	va_start(arg_ptr, s);
	while (l)
	{
		if (l->par)
			ft_printpar(l->content, arg_ptr, &ctr);
		else
			ft_print_content(l->content, &ctr);
		tmp = l;
		l = l->next;
		ft_elm_del(tmp, free);
	}
	va_end(arg_ptr);
	return (ctr);
}
