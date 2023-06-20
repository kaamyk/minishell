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

extern t_env	*g_env;

void	ft_check_double_input(t_data *data, char *s1, char *s2)
{
	int		input;
	char	*file;

	input = 0;
	if (s1[0] == '>' && s1[1] != '>')
		input++;
	if (s2[0] == '>' && s2[1] != '>')
		input++;
	if (input == 2)
	{
		data->double_input = true;
		file = ft_classify_str2(s1, '>');
		ft_redirection(data, NULL, file, true);
		free(file);
		data->double_input = false;
	}
}

/*
Send the commands
*/
void	ft_parsing7(t_tab *tab)
{
	t_data	data;
	int		i;

	data.tab_cmd = tab->tab_cmd;
	data.double_input = false;
	data.result = NULL;
	if (tab->nb_cmd > 1)
		data.print = false;
	i = 0;
	while (tab->tab_cmd[i])
	{
		data.run = false;
		if (tab->tab_cmd[i + 1] == 0)
			data.print = true;
		if (i > 0)
			ft_check_double_input(&data, data.str, tab->tab_cmd[i]);
		data.str = tab->tab_cmd[i];
		ft_classify_str(&data, tab->tab_cmd[i]);
		i++;
		if (tab->tab_cmd[i] == 0)
			free(data.result);
	}
	free_tab_mn(tab->tab_cmd);
}

void	ft_parsing6(t_tab *tab)
{
	char	*change;
	int		i;

	i = 0;
	while (tab->tab_cmd[i])
	{
		if (i > 0)
		{
			if (tab->tab_cmd[i][0] == '<'
				&& tab->tab_cmd[i - 1][0] != '<'
				&& tab->tab_cmd[i - 1][0] != '>'
				&& tab->tab_cmd[i - 1][0] != '|')
			{
				change = tab->tab_cmd[i];
				tab->tab_cmd[i] = tab->tab_cmd[i - 1];
				tab->tab_cmd[i - 1] = change;
			}
		}
		i++;
	}
	ft_parsing7(tab);
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
