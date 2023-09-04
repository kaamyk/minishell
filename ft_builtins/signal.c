/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:51:47 by xuluu             #+#    #+#             */
/*   Updated: 2023/08/31 18:52:08 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	g_run;

void	par_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_run = false;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
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
	if (signum == SIGINT)
		exit (2);
	else if (signum == SIGQUIT)
	{
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
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
