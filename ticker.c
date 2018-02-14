#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define TIMEOUT_SECS 2

int tick = 0;

void give_up(char *msg) {perror(msg); exit(1);}

void catchAlarm(int ignored) {
  tick += 1;
}

void catchQuit(int ignored) {
  printf("SIGQUIT handler called\n");
}

int main() {

  struct sigaction actAlarm;
  struct sigaction actQuit;

  actAlarm.sa_handler = catchAlarm;
  if (sigfillset(&actAlarm.sa_mask) < 0) {
    give_up("sigfillset");
  }
  actAlarm.sa_flags = 0;

  if (sigaction(SIGALRM, &actAlarm, 0) < 0) {
    give_up("sigaction");
  }

  actQuit.sa_handler = catchQuit;
  if (sigfillset(&actQuit.sa_mask) < 0) {
    give_up("sigfillset");
  }
  actQuit.sa_flags = 0;

  if (sigaction(SIGQUIT, &actQuit, 0) < 0) {
    give_up("sigaction");
  }

  do {
    alarm(TIMEOUT_SECS);
    pause();
    printf("Tick %i\n", tick);
  } while (1);
}

