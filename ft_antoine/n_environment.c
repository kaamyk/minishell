/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_environment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:30:55 by anvincen          #+#    #+#             */
/*   Updated: 2023/07/18 16:50:14 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_var_rank(char *input, char *key, char *value)
{
	char	*i_key;
	char	*i_value;
	int	i;

	i_key = init_keys(&inputs, 1);
	i_value = init_values(&inputs);
	i = 0;
	while (inputs[i])
	{
		if (ft_strncmp(key))
	}
}