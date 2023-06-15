/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:52:04 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/15 12:52:07 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_cmd2(t_data *data, char *str, int len, int n)
{
	int			i;

	data->cmd = (char *)malloc((len + 1) * sizeof(char));
	if (!data->cmd)
		return ;
	i = 0;
	while (i < len)
	{
		data->cmd[i] = str[i];
		i++;
	}
	data->cmd[i] = 0;
	data->cmd = del_char(data->cmd, '\'');
	data->cmd = del_char(data->cmd, '"');
	//printf("[%s]\n", data->cmd);
	while (str[n] != 0 && str[n] == ' ')
		n++;
	data->arg = ft_copy_str(&str[n]);
	ft_determine_command(data);
	free(data->cmd);
	free(data->arg);
}

void	ft_get_cmd(t_data *data, char *str)
{
	t_quotes	quote;
	int			len;

	len = 0;
	ft_get_value_quote(&quote);
	while (str[quote.i] != 0)
	{
		ft_check_quotes(&quote, str, quote.i);
		if (quote.open_s == 0 && quote.open_d == 0)
		{
			if (str[quote.i] == ' ')
				break ;
		}
		len++;
		quote.i++;
	}
	ft_get_cmd2(data, str, len, quote.i);
}
