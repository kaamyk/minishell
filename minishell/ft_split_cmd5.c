/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:41:34 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/15 12:41:38 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Send the commands
*/
void	ft_parsing6(t_tab *tab)
{
	t_data	data;
	int		i;

	if (tab->nb_cmd > 1)
		data.print = false;
	i = 0;
	while (tab->tab_cmd[i])
	{
		if (tab->tab_cmd[i + 1] == 0)
			data.print = true;
		//printf("[%d]\n", data.print);
		ft_classify_str(&data, tab->tab_cmd[i]);
		free(tab->tab_cmd[i]);
		i++;
	}
	free(tab->tab_cmd);
}

char	*ft_new_string(t_quotes *quote, char *str)
{
	char		*cmd;
	int			i;

	cmd = (char *)malloc((quote->i + 1) * sizeof(char));
	if (!cmd)
		return (0);
	i = 0;
	while (i < quote->i)
	{
		cmd[i] = str[i];
		i++;
	}
	cmd[i] = 0;
	cmd = ft_delete_space(cmd);
	return (cmd);
}

int	ft_without_quotes2(t_quotes *quote, t_tab *tab, char *str, int i)
{
	if (quote->open_s == 0 && quote->open_d == 0)
	{
		if (str[quote->i] == '|'
			|| str[quote->i] == '>'
			|| str[quote->i] == '<')
		{
			tab->nb_cmd++;
			tab->nb_signe++;
			tab->tab_position[i] = quote->i;
			i++;
			if (str[quote->i + 1] == '<' || str[quote->i + 1] == '>')
				quote->i++;
		}
	}
	return (i);
}
