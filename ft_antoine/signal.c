/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:51:47 by xuluu             #+#    #+#             */
/*   Updated: 2023/08/29 19:29:58 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_sig_exit_code = 0;

void	par_handler(int signum)
{
	printf("parent received signum == %d\n", signum);
	if (signum == SIGINT)
	{
		printf("SIGINT\n");
		// exit(EXIT_FAILURE);
	}
}

void	ignore_quit(void)
{
	struct sigaction	ign;

	ft_memset(&ign, 0, sizeof(ign));
	ign.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &ign, NULL);
}

void	parent_signal(bool a)
{
	struct sigaction	sig;

	ignore_quit();
	ft_memset(&sig, 0, sizeof(sig));
	sigemptyset(&sig.sa_mask);
	if (a == 0)
		sig.sa_handler = SIG_IGN;
	else
		sig.sa_handler = &par_handler;
	sigaction(SIGINT, &sig, NULL);
}

void	chi_handler(int signum)
{
	printf("child received signum == %d\n", signum);
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "SIGINT\n", 7);
		exit (2);
	}
	else if (signum == SIGQUIT)
	{
		write(STDOUT_FILENO, "SIGQUIT\n", 8);
		exit (3);
	}
}

void	child_signal(void)
{
	struct sigaction	sig;

	memset(&sig, 0, sizeof(sig));
	sigemptyset(&sig.sa_mask);
	sig.sa_handler = &chi_handler;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}








// void	ignore_quit(void)
// {
// 	t_sig	ignore;

// 	ft_memset(&ignore, 0, sizeof(ignore));
// 	ignore.sa_handler = SIG_IGN;
// 	sigaction(SIGQUIT, &ignore, NULL);
// }

// void	sig_handler(int signum)
// {
// 	if (signum == SIGINT)
// 	{
// 		g_sig_exit_code = 130;
// 		write(STDOUT_FILENO, "\n", 1);
// 		rl_on_new_line();
// 	}
// 	if (signum == SIGQUIT)
// 	{
// 		g_sig_exit_code = 131;
// 		rl_on_new_line();
// 	}
// }

// void	ft_signal_without_quit(t_data *data)
// {
// 	t_sig	sig;

// 	ignore_quit();
// 	ft_memset(&sig, 0, sizeof(sig));
// 	sig.sa_handler = sig_handler;
// 	sigaction(SIGINT, &sig, NULL);
// 	data->exit_code = g_sig_exit_code;
// 	g_sig_exit_code = 0;
// }

// void	ft_signal_with_quit(t_data *data)
// {
// 	t_sig	sig;

// 	ft_memset(&sig, 0, sizeof(sig));
// 	sig.sa_handler = sig_handler;
// 	sigaction(SIGINT, &sig, NULL);
// 	sigaction(SIGQUIT, &sig, NULL);
// 	data->exit_code = g_sig_exit_code;
// 	g_sig_exit_code = 0;
// }
