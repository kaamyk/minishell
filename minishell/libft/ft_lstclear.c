/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:03:03 by anvincen          #+#    #+#             */
/*   Updated: 2023/06/08 15:05:31 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*l_ptr;
	t_list	*nextlst;

	if (!lst || !del)
		return ;
	l_ptr = *lst;
	while (l_ptr)
	{
		nextlst = l_ptr->next;
		ft_lstdelone(l_ptr, del);
		l_ptr = nextlst;
	}
	*lst = NULL;
}
