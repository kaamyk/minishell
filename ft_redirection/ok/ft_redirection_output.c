/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_output.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 18:27:32 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/17 18:28:07 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/************************/
/* Redirections [<] [<<]*/
/************************/

/*
Change le valuer pour afficher pour la redirection << ou <
(< file) --> (< contenue_du_file)
(<< limiter) --> (<< contenue_du_input)
si (<< limiter) input est vide (just Enter) --> (;)
*/
void	ft_redirection_output2(t_data *data, int i, char *line)
{
	char	*tmp;

	if (data->tab_cmd[i + 1] != 0 && data->tab_cmd[i + 1][0] != '<')
	{
		if (line)
		{
			tmp = data->tab_cmd[i];
			data->tab_cmd[i] = ft_copy_str("<< ");
			free(tmp);
			data->tab_cmd[i] = ft_add_string(data->tab_cmd[i], line);
		}
		else
		{
			free(data->tab_cmd[i]);
			data->tab_cmd[i] = NULL;
		}
	}
}

void	ft_sleep(int limiter)
{
	int	time;

	time = 0;
	while (time < limiter)
		time++;
}

void	ft_redirection_output(t_data *data, int i)
{
	char	*limiter;
	char	*line;

	limiter = ft_find_str(data->tab_cmd[i]);
	line = NULL;
	if (data->tab_cmd[i][1] == '<')
	{
		line = ft_redirection3(limiter);
		ft_redirection_output2(data, i, line);
	}
	else
	{
		ft_sleep(21474836);
		line = ft_redirection2(data, limiter);
		if (line)
			printf("%s", line);
	}
	free(limiter);
	free(line);
}

bool	ft_check_infile(t_data *data)
{
	int		i;
	bool	check;
	char	**tab;

	check = false;
	tab = data->tab_cmd;
	i = 0;
	while (tab[i])
	{
		if (tab[i][0] == '<')
		{
			check = true;
			if (tab[i][1] == '<')
				ft_redirection_output(data, i);
		}
		i++;
	}
	return (check);
}
