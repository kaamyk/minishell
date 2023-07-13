/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:09:43 by xuluu             #+#    #+#             */
/*   Updated: 2023/07/07 15:10:32 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*********************************/
/* Add space center the command  */
/*********************************/

char	*ft_signe_space_str(char *str, int len)
{
	int		i;
	int		m;
	char	*new_str;

	new_str = (char *)malloc((len + 1) * sizeof(char));
	if (!new_str)
		return (0);
	i = 0;
	m = 0;
	while (str[i])
	{
		if (i > 0 && str[i] != '|' && str[i] != '>' && str[i] != '<')
		{
			if (str[i - 1] == '|' || str[i - 1] == '>' || str[i - 1] == '<')
			{
				new_str[m] = ' ';
				m++;
			}
		}
		new_str[m] = str[i];
		m++;
		i++;
	}
	new_str[m] = 0;
	return (new_str);
}

char	*ft_order_with_space(char *str)
{
	int		i;
	int		nb_signe;
	int		len;
	char	*new_str;

	nb_signe = 0;
	i = 0;
	while (str[i])
	{
		if (i > 0 && str[i] != '|' && str[i] != '>' && str[i] != '<')
		{
			if (str[i - 1] == '|' || str[i - 1] == '>' || str[i - 1] == '<')
				nb_signe++;
		}
		i++;
	}
	len = ft_strlen(str) + nb_signe;
	new_str = ft_signe_space_str(str, len);
	free(str);
	return (new_str);
}
