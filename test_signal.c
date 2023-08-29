#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <signal.h>

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

	memset(&ign, 0, sizeof(ign));
	ign.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &ign, NULL);
}

void	parent_signal(bool a)
{
	struct sigaction	sig;

	ignore_quit();
	memset(&sig, 0, sizeof(sig));
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

int	main(void)
{
	int	pid = getpid();
	int	fork_pid = fork();
	int	w_pid = 0;
	int	status;
	int	save_status = 0;

	printf(">>> PARENT PID == %d\n", pid);
	parent_signal(1);
	if (fork_pid == 0)
	{
		child_signal();
		write(STDOUT_FILENO, "entering child process\n", 23);
		printf(">>> CHILD PID == %d\n", getpid());
		for (size_t i = 0; i < 10; i++)
		{
			printf("i == %ld\n", i);
			sleep(1);
		}
		write(STDOUT_FILENO, "ici\n", 4);
		exit(EXIT_SUCCESS);
	}
	else
	{
		parent_signal(0);
		while (w_pid != -1 || errno != ECHILD)
		{
			w_pid = waitpid(fork_pid, &status, 0);
			if (w_pid == fork_pid)
				save_status = status;
			continue ;
		}
		printf("After while w_pid == %d\n", w_pid);
		parent_signal(1);
		save_status /= 256;
		printf("save_status == %d\n", save_status);
		if (WIFSIGNALED(save_status))
		{
			printf("WIFSIGNALED\n");
			status = 128 + WTERMSIG(save_status);
		}
		else if (WIFEXITED(save_status))
		{
			printf("WIFEXITED\n");
			int exit_status = WEXITSTATUS(status);
            printf("Child process exited with status: %d\n", exit_status);
			status = WEXITSTATUS(status);
		}
		else
			status = save_status;
		printf(">>> FIN status == %d\n", status);
	}
	return (0);
}
