/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_environment_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:30:55 by anvincen          #+#    #+#             */
/*   Updated: 2023/07/18 16:51:57 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_double(char *inputs, char **e_key, char **e_value)
{
	char	*i_key;
	char	*i_value;
	size_t	l_value;
	size_t	l_val_env;
	size_t	i;

	printf(">>>check_double\n");
	i_key = init_keys(&inputs, 1);
	printf("\t|=>i_key == %s\n", i_key);
	i_value = init_values(&inputs);
	printf("\t|=>i_value == %s\n", i_value);
	i = 0;
	while (e_key[i])
	{
		if (ft_compare_str(i_key, e_key) == 1)
		{
			l_val_env = 0;
			if (e_value[i] != NULL)
				l_val_env = ft_strlen(e_value[i]);
			if ((l_val_env != 0 && l_value == 0) || (e_value[i] != NULL
					&& ft_compare_str(e_value[i], value) == false))
				return (1);
		}
		++i;
	}
	return (0);
}
