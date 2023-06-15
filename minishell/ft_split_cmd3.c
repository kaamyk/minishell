/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:46:51 by xuluu             #+#    #+#             */
/*   Updated: 2023/06/13 12:46:54 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* copy part 2 */
char	*ft_redirec7(char *str)
{
	t_quotes	quote;
	int			len;
	char		*cmd;
	int			i;

	len = ft_strlen(str);
	cmd = (char *)malloc((len + 1) * sizeof(char));
	if (!cmd)
		return (0);
	i = 0;
	ft_get_value_quote(&quote);
	while (str[quote.i] != 0)
	{
		ft_check_quotes(&quote, str, quote.i);
		if (quote.open_s == 0 && quote.open_d == 0)
		{
			if (str[quote.i] == '>' || str[quote.i] == '<')
				break ;
		}
		cmd[i] = str[quote.i];
		i++;
		quote.i++;
	}
	cmd[i] = 0;
	return (cmd);
}

/* copy part 1 */
char	*ft_redirec6(char *str, char *cmd)
{
	t_quotes	quote;
	int			i;

	i = 0;
	ft_get_value_quote(&quote);
	while (str[quote.i] != 0)
	{
		ft_check_quotes(&quote, str, quote.i);
		if (quote.open_s == 0 && quote.open_d == 0)
		{
			if (str[quote.i] == ' '
				|| str[quote.i] == '>'
				|| str[quote.i] == '<')
				break ;
		}
		cmd[i] = str[quote.i];
		i++;
		quote.i++;
	}
	cmd[i] = 0;
	return (cmd);
}

void	ft_redirec5(t_quotes *quote, t_redirec *redirec, char *str)
{
	int		len;
	char	*cmd;

	len = ft_strlen(str);
	cmd = (char *)malloc((len + 1) * sizeof(char));
	if (!cmd)
		return ;
	redirec->string = ft_redirec6(&str[quote->i], cmd);
	redirec->tmp = redirec->p1;
	redirec->p1 = ft_strjoin(redirec->p1, redirec->string);
	free(redirec->tmp);
	quote->i += ft_strlen(redirec->string);
	free(redirec->string);
}

/* start copy */
void	ft_redirec4(t_quotes *quote, t_redirec *redirec, char *str)
{
	if (redirec->time == 0)
	{
		redirec->p1 = ft_copy_str(redirec->signe);
		free(redirec->signe);
		ft_redirec5(quote, redirec, str);
		redirec->p2 = ft_redirec7(&str[quote->i]);
		redirec->time++;
	}
	else
	{
		redirec->tmp = redirec->p1;
		redirec->p1 = ft_strjoin(redirec->p1, redirec->signe);
		free(redirec->tmp);
		free(redirec->signe);
		ft_redirec5(quote, redirec, str);
		redirec->string = ft_redirec7(&str[quote->i]);
		redirec->tmp = redirec->p2;
		redirec->p2 = ft_strjoin(redirec->p2, redirec->string);
		free(redirec->tmp);
		free(redirec->string);
	}
}

/* copy signe */
char	*ft_redirec3(char *str)
{
	int		i;
	char	*signe;

	signe = (char *)malloc(3 * sizeof(char));
	if (!signe)
		return (0);
	i = 0;
	while (str[i] != 0 && (str[i] == '>' || str[i] == '<'))
	{
		signe[i] = str[i];
		i++;
	}
	signe[i] = 0;
	return (signe);
}
