// command for shell: test_sig_handler
#include "types.h"
#include "stat.h"
#include "user.h"
#define SIG_TEST 18
volatile int keep_running = 1;

void
callback_for_SIG_TEST(int signum){
	keep_running = 0;
}

int
main(int argc, char *argv[])
{
  struct sigaction sigaction_for_SIG_TEST = {.sa_handler = &callback_for_SIG_TEST, .sigmask = 0};
  struct sigaction old_sigaction;
  sigaction( SIG_TEST, sigaction_for_SIG_TEST, &old_sigaction );
  int number_of_iterations = 100, iter_num = 0;
  int pid = fork();
  if (pid == 0){ //child
    while(keep_running && iter_num < number_of_iterations){
      printf(1, "child is running, waiting for SIG_TEST.\n");
      iter_num++;
    }
    if (iter_num < number_of_iterations){
      printf(1, "child got signal SIG_TEST!!\n");
    }
    exit();
  } else { //parent
    for(int i = 0; i < number_of_iterations/4; i++){
      printf(1, "parent iteration no. : %d\n", i);
    }
    printf(1, "parent send signal SIG_TEST to child\n");
    kill(pid, SIG_TEST);
    printf(1, "parent waits to the child to exit\n");
    wait();
    printf(1, "parent's pid is : %d, child's pid is: %d\n", getpid(), pid );
    printf(1, "parent exits\n");
  }
  exit();
}
