/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_classify_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:07:54 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/13 17:08:50 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_access(char *file)
{
	int	result;

	result = access(file, F_OK);
	if (result != 0)
		ft_error(NO_SUCH, file, 0);
	return (result);
}

void	ft_classify_str2(char *str, int signe)
{
	int		i;
	char	*file;

	i = 0;
	while (str[i] != 0 && str[i] == ' ')
		i++;
	file = ft_copy_str(&str[i]);
	if (signe == 2 && ft_access(file) == 0)
		printf("[%s][%d]\n", file, signe);
	else if (signe == 4)
		ft_redirection4(file);
	free(file);
}

void	ft_classify_str(t_data *data, char *str)
{
	//printf("[%s]\n", str);
	if (str[0] != '>' && str[0] != '<')
		ft_get_cmd(data, str);
	if (str[0] == '|')
		printf("[ | ]\n");
	else if (str[0] == '>' && str[1] != '>')
		ft_classify_str2(&str[1], 1);
	else if (str[0] == '<' && str[1] != '<')
		ft_classify_str2(&str[1], 2);
	else if (str[0] == '>' && str[1] == '>')
		ft_classify_str2(&str[2], 3);
	else if (str[0] == '<' && str[1] == '<')
		ft_classify_str2(&str[2], 4);
}
