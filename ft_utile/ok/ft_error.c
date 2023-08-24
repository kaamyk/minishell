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

void	ft_error2(t_error error)
{
	printf("bash: ");
	if (error == SYNTAXE)
		printf("syntaxe error near unexpected token ''.");
	else if (error == NOT_FOUND)
		printf(": command not found.");
	else if (error == DIRECTORY)
		printf(": Is a directory");
	else if (error == NOT_VALID)
		printf(": '': not a valid identifier.");
	else if (error == NO_SUCH)
		printf(": No such file or directory");
	else if (error == NOT_ACCESS)
		printf(": Permission non accordée");
	printf("\n");
}

void	ft_error(t_error error, char *command, char *option)
{
	if (command)
	{
		printf("bash: ");
		if (error == SYNTAXE)
			printf("syntaxe error near unexpected token '%c'.", command[0]);
		else if (error == NOT_FOUND)
			printf("%s: command not found.", command);
		else if (error == DIRECTORY)
			printf("%s: Is a directory", command);
		else if (error == NOT_VALID)
			printf("%s: '%s': not a valid identifier.", command, option);
		else if (error == NO_SUCH)
			printf(": No such file or directory");
		else if (error == NOT_ACCESS)
			printf("%s: Permission non accordée", command);
		printf("\n");
	}
}
