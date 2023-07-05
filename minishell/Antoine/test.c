#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void	sig_handler(int signum)
{
	printf("signum == %d\n", signum);
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		//printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(void)
{
	char		*line;
	t_sig		s_sig;

	s_sig.sa_handler = sig_handler;
	sigemptyset(&s_sig.sa_mask);
	s_sig.sa_flags = 0;
	sigaddset(&s_sig.sa_mask, SIGQUIT);
	sigaction(SIGINT, &s_sig, NULL);
	sigaction(SIGQUIT, &s_sig, NULL);
	//signal(SIGINT, sig_handler);
	while (1)
	{
		line = get_line();
		ft_read_line(line);
