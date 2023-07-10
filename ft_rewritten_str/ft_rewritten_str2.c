/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:54:49 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/13 11:54:56 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_copy_str(char *str)
{
	char	*arg;
	int		len;

	len = ft_strlen(str);
	arg = (char *)malloc((len + 1) * sizeof(char));
	if (!arg)
		return (0);
	arg = ft_memcpy(arg, str, len);
	arg[len] = 0;
	return (arg);
}

void	ft_without_quotes(t_quotes *quote, t_redirec *redirec, char *str)
{
	if (quote->open_s == 0 && quote->open_d == 0)
	{
		if (str[quote->i] == '>' || str[quote->i] == '<')
		{
			redirec->signe = ft_redirec3(&str[quote->i]);
			if (redirec->time == 0)
				redirec->stop = quote->i;
			while (str[quote->i] == '>'
				|| str[quote->i] == '<'
				|| str[quote->i] == ' '
				|| str[quote->i] == '\t')
				quote->i++;
			if (str[quote->i] != 0
				&& str[quote->i] != '>'
				&& str[quote->i] != '<')
				ft_redirec4(quote, redirec, str);
		}
	}
}

/* find position copy */
void	ft_redirec2(t_redirec *redirec, char *str)
{
	t_quotes	quote;

	redirec->time = 0;
	redirec->stop = 0;
	ft_get_value_quote(&quote);
	while (str[quote.i] != 0)
	{
		ft_check_quotes(&quote, str, quote.i);
		ft_without_quotes(&quote, redirec, str);
		if (str[quote.i] != 0 && str[quote.i] != '>' && str[quote.i] != '<')
			quote.i++;
		else if (quote.open_s == 1 || quote.open_d == 1)
			quote.i++;
	}
}

char	*ft_redirec8(t_redirec *redirec, char *str)
{
	int		i;
	int		len;
	char	*cmd;

	len = ft_strlen(str);
	cmd = (char *)malloc((len + 1) * sizeof(char));
	if (!cmd)
		return (0);
	i = 0;
	while (i < redirec->stop)
	{
		cmd[i] = str[i];
		i++;
	}
	cmd[i] = 0;
	cmd = ft_add_string(cmd, redirec->p2);
	cmd = ft_add_string(cmd, redirec->p1);
	return (cmd);
}

char	*ft_rewritten_with_redirection(char *str)
{
	t_redirec	redirec;
	char		*cmd;

	ft_redirec2(&redirec, str);
	if (str[0] == '>' || str[0] == '<')
		cmd = ft_strjoin(redirec.p2, redirec.p1);
	else
		cmd = ft_redirec8(&redirec, str);
	free(redirec.p1);
	free(redirec.p2);
	free(str);
	return (cmd);
}
