/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:30:55 by anvincen          #+#    #+#             */
/*   Updated: 2023/05/16 18:01:45 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_data *data)
{
	printf("FREE_ALL\n");
	free(data->arg);
	exit (1);
}

void	sig_handler(int signal, siginfo_t *info, void *a)
{
	printf("SIG_HANDLER\n");
	t_data	*data;

	printf("signal == %d\n", signal);
	data = (t_data *)a;
	if (signal == SIGINT)
		free_all(data);
}

void	read_line(t_data *data)
{
	data->arg = readline(">>>");
	printf("arg == %s\n", data->arg);
	free(data->arg);
}

int	main(void)
{
	struct sigaction	s_sig;
	t_data				data;

	data.finished = false;
	s_sig.sa_sigaction = sig_handler;
	s_sig.sa_flags = SA_SIGINFO;
	sigemptyset(&s_sig.sa_mask);
	sigaction(SIGINT, &s_sig, 0);
	while (data.finished == false)
	{
		read_line(&data);
	}
	return (0);
}
