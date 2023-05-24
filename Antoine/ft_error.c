/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:18:21 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/23 12:23:54 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(t_error error, char *command, char *option)
{
	printf("bash: ");
	if (error == SYNTAXE)
		printf("syntaxe error near unexpected token '%s'", command);
	else if (error == NOT_FOUND)
		printf("%s: command not found", command);
	else if (error == DIRECTORY)
		printf("%s: Is a directory", command);
	else if (error == NOT_VALID)
		printf("%s: '%s': not a valid identifier", command, option);
	printf("\n");
}
