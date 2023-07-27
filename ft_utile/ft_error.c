/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:18:21 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/26 09:49:33 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(t_error error, char *command, char *option)
{
	printf(RED "bash: ");
	if (error == SYNTAXE)
		printf("syntaxe error near unexpected token '%c'.", command[0]);
	else if (error == NOT_FOUND)
		printf("%s: command not found.", command);
	else if (error == DIRECTORY)
		printf("%s: Is a directory", command);
	else if (error == NOT_VALID)
		printf("%s: '%s': not a valid identifier.", command, option);
	else if (error == NO_SUCH)
		printf("%s: No such file or directory", command);
	else if (error == NOT_ACCESS)
		printf("%s: Permission non accordée", command);
	printf("\n" RESET);
}
