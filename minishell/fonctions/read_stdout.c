#include <unistd.h>
#include <stdio.h>

int main()
{
  fprintf(stdout, "this is from stdout\n");
  int outfd[2];
  int infd[2];
  int errfd[2];

  //pipes for parent to write and read
  pipe(outfd);
  pipe(infd);
  pipe(errfd);

  if(!fork()) {
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    close(STDIN_FILENO);
    dup2(outfd[0], STDIN_FILENO);
    dup2(errfd[1], STDERR_FILENO);
    dup2(infd[1], STDOUT_FILENO);
    close(outfd[0]); /* Not required for the child */
    close(outfd[1]);
    close(errfd[0]);
    close(errfd[1]);
    close(infd[0]);
    close(infd[1]);

    char *argv[]={ "child", 0};
    execv(argv[0], argv);
  } else {
    char buffer[1024];
    int count;

    /* close fds not required by parent */
    close(outfd[0]);
    close(errfd[1]);
    close(infd[1]);

    // Write to child’s stdin
    write(outfd[1], "2^32\n", 5);

    // Read from child’s stderr
    count = read(errfd[0], buffer, sizeof(buffer)-1);
    if (count >= 0) {
      buffer[count] = 0;
      printf("%s", buffer);
    } else {
      printf("IO Error\n");
      printf("%d\n", count);
    }

    // Read from child’s stdout
    count = read(infd[0], buffer, sizeof(buffer)-1);
    if (count >= 0) {
      buffer[count] = 0;
      printf("%s", buffer);
    } else {
      printf("IO Error\n");
    }

  }
}