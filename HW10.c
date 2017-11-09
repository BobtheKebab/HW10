#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

static void sighandler (int signo) {

  if (signo == SIGINT) {
    int fd = open("log", O_WRONLY | O_APPEND);
    char * temp = "Program exited due to SIGINT\n";
    printf("%s", temp);
    write(fd, temp, 1000);
    close(fd);
    exit(0);
  }

  if (signo == SIGUSR1) {
    printf("Parent Process: %d\n", getppid());
  }
  
}

int main () {

  signal(SIGINT, sighandler);
  signal(SIGUSR1, sighandler);
  
  while (1) {
    printf("PID: %d\n", getpid());
    sleep(1);
  }

  return 0;
  
}
