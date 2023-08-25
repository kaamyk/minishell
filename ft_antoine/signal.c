/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:51:47 by xuluu             #+#    #+#             */
/*   Updated: 2023/08/25 18:43:35 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_sig_exit_code = 0;

void	ignore_quit(void)
{
	struct sigaction	ignore;

	ft_memset(&ignore, 0, sizeof(ignore));
	ignore.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &ignore, NULL);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_sig_exit_code = 130;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
	}
	if (signum == SIGQUIT)
	{
		g_sig_exit_code = 131;
		rl_on_new_line();
	}
}

void	ft_signal_without_quit(t_data *data)
{
	t_sig	sig;

	ignore_quit();
	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_handler = sig_handler;
	sigaction(SIGINT, &sig, NULL);
	data->exit_code = g_sig_exit_code;
	g_sig_exit_code = 0;
}

void	ft_signal_with_quit(t_data *data)
{
	t_sig	sig;

	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_handler = sig_handler;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
	data->exit_code = g_sig_exit_code;
	g_sig_exit_code = 0;
}
