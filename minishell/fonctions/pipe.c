// #include <stdlib.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <string.h>

// int main()
// {
//     int n;
//     int filedes[2];
//     char buffer[1025];
//     char *message = "Hello, World!";

//     pipe(filedes);
//     write(filedes[1], message, strlen(message));

//     if ((n = read ( filedes[0], buffer, 1024 ) ) >= 0) {
//         buffer[n] = 0;  //terminate the string
//         printf("read %d bytes from the pipe: %s\n", n, buffer);
//     }  
//     else
//         perror("read");
//     exit(0);
// }

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

// int main()
// {
//         int     filedes[2], nbytes;
//         pid_t   childpid;
//         char    string[] = "Hello, world!\n";
//         char    readbuffer[80];

//         pipe(filedes);
       
//         if((childpid = fork()) == -1)
//         {
//                 perror("fork");
//                 exit(1);
//         }

//         if(childpid == 0)
//         {
//                 close(filedes[0]);//Child process does not need this end of the pipe

//                 /* Send "string" through the output side of pipe */
//                 write(filedes[1], string, (strlen(string)+1));
//                 exit(0);
//         }
//         else
//         {
//                 /* Parent process closes up output side of pipe */
//                 close(filedes[1]);//Parent process does not need this end of the pipe

//                 /* Read in a string from the pipe */
//                 nbytes = read(filedes[0], readbuffer, sizeof(readbuffer));
//                 printf("Read string: %s", readbuffer);
//         }
       
//         return(0);
// }

/*****************************************************************************/
// int main(int ac, char **av)
// {
// 	int		fd[2];
// 	int		status;
// 	pid_t	id;
// 	// char	*argVec[] = {"pwd", NULL};
// 	// char	*argVec2[] = {"grep", "a", NULL};

// 	pipe(fd);
// 	id = fork();
// 	if (id == 0)
// 	{
// 		dup2(fd[1], STDOUT_FILENO);
// 		execlp(av[1], av[1], (char *)NULL);
// 	}

// 	id = fork();
// 	if (id == 0)
// 	{
// 		close(fd[1]);
// 		//printf("%s\n", av[2]);
// 		dup2(fd[0], STDIN_FILENO);
// 		execlp(av[2], av[2], (char *)NULL);
// 	}

// 	close(fd[0]);
// 	close(fd[1]);

// 	waitpid(-1, &status, 0);
// 	waitpid(-1, &status, 0);
// }

/****************************************************************************/

void	ft_parent_process(int fd, char **cmd)
{
	waitpid(-1, &status, 0);
	dup2(fd, ...);
	dup2(port[0], ...);
	close(port[1]);
	close(fd);
	execve(cmd[0], cmd, NULL);
	exit(EXIT_FAILURE);
}

void	ft_child_process(int fd, char **cmd)
{
	dup2(fd, STDIN_FILENO);
	dup2(port[1], STDOUT_FILENO);
	close(port[0]);
	close(fd);
	execve(cmd[0], cmd, NULL);
	exit(EXIT_FAILURE);
}

void	pipex(int f1, int f2, char *cmd1, char *cmd2)
{
	int		status;
	int		port[2];
	pid_t	id;
	pid_t	id2;

	pipe(port);

	id = fork();
	if (id < 0)
		return (perror("Fork: "));
	if (id == 0)
	{
		ft_child_process(fd, )
	}

	id2 = fork();
	if (id2 < 0)
		return (perror("Fork: "));
	if (id2 == 0)
	{
		ft_parent_process(fd2, );
	}

	close(port[0]);
	close(port[1]);
	waitpid(id, &status, 0);
	waitpid(id2, &status, 0);
	return (0);
}

char	*ft_get_path(char *cmd, bool found)
{
	DIR				*dp;
	struct dirent	*dirp;
	char			*path;

	dp = opendir("/usr/bin");
	dirp = readdir(dp);
	while (dirp != NULL)
	{
		if (ft_compare_str(cmd, dirp->d_name) == true)
		{
			path = ft_strjoin("/usr/bin/", cmd);
			found = true;
		}
		dirp = readdir(dp);
	}
	if (closedir(dp) == -1)
		perror("closedir");
	if (found == true)
		return (path);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	int		f1;
	int		f2;
	char	*cmd1;
	char	*cmd2;

	f1 = open(av[1], O_RDONLY);
	f2 = open(av[2], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f1 < 0 || f2 < 0)
		return (-1);
	cmd1 = ft_get_path(av[3]);
	cmd2 = ft_get_path(av[4]);
	pipex(f1, f2, av[3], av[4]);
	return (0);
}
