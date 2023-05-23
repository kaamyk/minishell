/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 10:11:50 by anvincen          #+#    #+#             */
/*   Updated: 2022/12/22 09:37:25 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_cpylst(t_list *lst, int mult, int lastlen)
{
	char	*s;
	t_list	*l_tmp;
	int		i;
	int		j;

	s = ft_calloc_gnl(BUFFER_SIZE * mult + lastlen + 1, 1);
	if (!s || !lst || !lst->content)
		return (NULL);
	l_tmp = lst;
	i = 0;
	while (l_tmp)
	{
		j = 0;
		while (l_tmp->content[j] && ++i && ++j)
		{
			s[i - 1] = l_tmp->content[j - 1];
			if (s[i - 1] == '\n' && ft_lstclear(&lst, free))
				return (s);
		}
		l_tmp = l_tmp->next;
	}
	ft_lstclear(&lst, free);
	return (s);
}

char	*ft_resetrest(char *rest, char *s, int i)
{
	char	tmp;
	int		j;

	j = 0;
	while (s && rest[i] && i < BUFFER_SIZE && ++i && ++j)
	{
		tmp = rest[i - 1];
		rest[j - 1] = tmp;
	}
	while (j < BUFFER_SIZE && ++j)
		rest[j - 1] = 0;
	return (s);
}

char	*ft_readfile(int fd)
{
	static char	rest[BUFFER_SIZE + 1];
	char		*s;
	int			i;
	int			j;

	s = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	i = 0;
	while (s && rest[i] && i < BUFFER_SIZE && ++i)
	{
		s[i - 1] = rest[i - 1];
		if (s[i - 1] == '\n')
			return (ft_resetrest(rest, s, i));
	}
	ft_resetrest(rest, s, i);
	if (!*rest && !read(fd, rest, BUFFER_SIZE))
		return (s);
	j = 0;
	while (s && rest[j] && i < BUFFER_SIZE && ++j && ++i)
	{
		s[i - 1] = rest[j - 1];
		if (s[i - 1] == '\n')
			return (ft_resetrest(rest, s, j));
	}
	ft_resetrest(rest, s, j);
	return (s);
}

int	ft_lstnew(t_list **n_elm, int fd)
{
	int	i;

	*n_elm = malloc (sizeof(t_list));
	if (!*n_elm)
		return (1);
	(*n_elm)->content = ft_readfile(fd);
	(*n_elm)->next = NULL;
	i = 0;
	while (i < BUFFER_SIZE && ++i)
	{
		if (!(*n_elm)->content[0] || (*n_elm)->content[i - 1] == '\n')
			return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	t_list	*n_elm;
	t_list	*l;
	t_list	*tmp;
	char	*s;
	int		i;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	l = NULL;
	i = 0;
	while (!ft_lstnew(&n_elm, fd) && ++i && n_elm->content)
	{
		if (!l)
			ft_assigne(&l, &n_elm, &tmp, 0);
		else
			ft_assigne(&tmp, &n_elm, &tmp, 1);
	}
	if (n_elm->content[0] && !i)
		ft_assigne(&l, &n_elm, &tmp, 0);
	else if (i)
		ft_assigne(&tmp, &n_elm, &tmp, 1);
	else if (!n_elm->content[0] && !i)
		return (ft_lstdelone(n_elm, free));
	s = ft_cpylst(l, i, ft_nlinstr(tmp->content));
	return (s);
}

/*int	main(void)
{
	int		file;
	char	*str;
	int		i = 0;

	file = open("./big_line_no_nl", O_RDONLY);
	if (!file)
	{
		printf("Pas de file\n");
		return (0);
	}
	while (i < 1)
	{
		str = get_next_line(102);
		//printf ("main fin str ==	%p\n", str);
		printf ("str == '%s'\n", str);
		free(str);
		i++;
	}
	close(file);
}*/