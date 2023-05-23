/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:30:55 by anvincen          #+#    #+#             */
/*   Updated: 2023/05/23 15:12:21 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signal)
{
	//printf("SIG_HANDLER\n");
	if (signal == SIGINT || signal == SIGQUIT)
		rl_on_new_line();
	else if (signal == EOF)
		exit (2);
}

void	read_line(t_data *data)
{
	data->arg = readline(">>>");
	
	printf("data->arg == %s\n", data->arg);
	if (data->arg == NULL)
		exit (1);
	printf("arg == %s\n", data->arg);
	free(data->arg);
}

int	main(void)
{
	t_sig	s_sig;
	t_data	data;

	data.finished = false;
	s_sig.sa_handler = signal_handler;
	s_sig.sa_flags = 0;
	sigemptyset(&s_sig.sa_mask);
	sigaction(SIGINT, &s_sig, 0);
	sigaction(SIGQUIT, &s_sig, 0);
	while (data.finished == false)
	{
		read_line(&data);
	}
	return (0);
}
