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

  char line[100];
  int out_pipe, in_pipe;

  out_pipe = open("out", O_WRONLY);
  in_pipe = open("in", O_WRONLY);
  printf("fifos opened!\n");

  while (1) {
    printf("input a number to add: ");
    fgets(line, sizeof(line), stdin);
    *strchr(line, '\n') = 0;

    write(in_pipe, line, sizeof(line));
    read(out_pipe, line, sizeof(line));
    printf("sum so far: %d\n", line);
  }

  close(out_pipe);
  close(in_pipe);

  return 0;

}
