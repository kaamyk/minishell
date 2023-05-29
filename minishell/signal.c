/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:51:47 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/23 17:38:05 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_signal(void)
{
	t_sig	sig;

	ignore_quit();
	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_handler = sig_handler;
	sigaction(SIGINT, &sig, NULL);
}
