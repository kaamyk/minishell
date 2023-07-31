/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:37:47 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/10 14:38:24 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_find_c(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_count_signe(char *str)
{
	int	i;
	int	nb_signe;

	nb_signe = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' && i > 0)
		{
			if (str[i - 1] == '>' || str[i - 1] == '<')
				nb_signe++;
		}
		i++;
	}
	return (nb_signe);
}

int	ft_nb_c(char *str, char c)
{
	int	i;
	int	nombre;

	i = 0;
	nombre = 0;
	while (str[i])
	{
		if (str[i] == c)
			nombre++;
		i++;
	}
	return (nombre);
}

char	*ft_find_str(char *str)
{
	char	*limiter;
	char	**tab;

	limiter = NULL;
	tab = ft_split_mn(str, ' ');
	limiter = ft_copy_str(tab[1]);
	ft_free_tab(tab);
	return (limiter);
}

void	ft_free_end(t_data *data)
{
	if (data->s_bonus)
	{
		free(data->tab_logic);
		ft_free_tab(data->tab_cmd_logic);
	}
	ft_free_tab_with_len(data->tab_cmd, data->nb_cmd);
	free_list(data->env);
}
