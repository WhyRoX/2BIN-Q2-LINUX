#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "utils.h"

void sig_handler(int sig) {
  const char *name = strsignal(sig);
  if (name == NULL) {
    name = "(null)";
  }
  printf(" Signal '%s' recu ", name);
  fflush(stdout);
}

int main() {
  printf("[%d] Hello, I am TIMER! ;)\n", getpid());
  for (int sig = 1; sig <= 31; sig++) {
    if (sig == SIGKILL || sig == SIGSTOP) {
      printf("Signal %d (%s) non capture\n", sig, strsignal(sig));
      continue;
    }

    ssigaction(sig, sig_handler);
  }

  while (1) {
    ssize_t res = write(STDOUT_FILENO, ".", 1);
    if (res < 0 && errno != EINTR) {
      perror("write");
    }
    sleep(1);
  }

  return 0;
}