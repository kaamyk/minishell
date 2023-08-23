/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:18:21 by xuluu             #+#    #+#             */
/*   Updated: 2023/08/23 16:45:29 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			printf("%s: No such file or directory", command);
		else if (error == NOT_ACCESS)
			printf("%s: Permission non accordée", command);
		printf("\n");
	}
}

void	export_error(t_data *data, char **env, char *unvalid_var)
{
	write(STDERR_FILENO, "bash: export: `", 15);
	write(STDERR_FILENO, unvalid_var, ft_strlen(unvalid_var));
	write(STDERR_FILENO, "': not a valid identifier\n", 26);
	data->exit_code = 1;
	return (env);
}
