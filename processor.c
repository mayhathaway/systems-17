#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

static void sighandler(int signo) {
  if (signo == SIGINT) {
    printf("program exited \n");
    remove("out");
    remove("in");
    exit(0);
  }
}

int main() {

  signal(SIGINT, sighandler);

  int buffer, sum, out_pipe, in_pipe;
  sum = 0;
  mkfifo("in", 0644);
  mkfifo("out", 0644);

  while (1) {
    in_pipe = open("in", O_RDONLY);
    read(in_pipe, &buffer, sizeof(buffer));
    close(in_pipe);
    sum += buffer;

    out_pipe = open("out", O_WRONLY);
    write(out_pipe, &sum, sizeof(sum));
    close(out_pipe);
  }

  return 0;
}
