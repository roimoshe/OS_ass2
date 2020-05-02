#include "types.h"
#include "stat.h"
#include "user.h"
#define SIG_TEST 18
int keep_running = 1;

void
callback_for_SIG_TEST(int signum){
	keep_running = 0;
}

int
main(int argc, char *argv[])
{
  struct sigaction sigaction_for_SIG_TEST = {.sa_handler = &callback_for_SIG_TEST, .sigmask = 0};
  struct sigaction old_sigaction;
  sigaction( SIG_TEST, &sigaction_for_SIG_TEST, &old_sigaction );
  int number_of_iterations = 100;
  int pid = fork();
  if (pid == 0){ //child
    while(keep_running){
      printf(1, "child is running\n");
    }
    printf(1, "child got signal no. : %d\n child exits\n", SIG_TEST);
    exit();
  } else { //parent
    for(int i = 0; i < number_of_iterations/2; i++){
      printf(1, "parent: %d\n", i);
    }
    kill(pid, SIG_TEST);
  }
  exit();
}
