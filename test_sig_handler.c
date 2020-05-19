// command for shell: test_sig_handler
#include "types.h"
#include "stat.h"
#include "user.h"
#define SIG_TEST 7
volatile int keep_running = 1;


void
callback_for_SIG_TEST(int signum){
  char c = '@'+signum;
  c-=SIG_TEST;
  // char c = '@';
  write(1, &c, 1);
  keep_running = 0;
}

int
main(int argc, char *argv[])
{
  struct sigaction sigaction_for_SIG_TEST = {.sa_handler = callback_for_SIG_TEST, .sigmask = 0};
  struct sigaction old_sigaction;
  int wait_ret_value;
  if( sigaction( SIG_TEST, &sigaction_for_SIG_TEST, &old_sigaction ) < 0){
    printf(1, "error in sigaction!\n");
  }
  int number_of_iterations = 100, iter_num = 0;
  int pid = fork();
  if (pid < 0){
    printf(1, "error in fork!\n");
    exit();
  } else if (pid == 0){ //child
    while(keep_running && iter_num < number_of_iterations){
      printf(1, "childID %d is running, waiting for SIG_TEST.\n", pid);
      iter_num++;
    }
    if (iter_num < number_of_iterations){
      printf(1, "childID %d got signal SIG_TEST!!\n", pid);
    } else {
      printf(1, "child exists without getting signal SIG_TEST :(  :(  \n");
    }
    exit();
  } else { //parent
    for(int i = 0; i < number_of_iterations/10; i++){
      printf(1, "pid:%d, parent iteration no. : %d\n", getpid(), i);
    }
    printf(1, "parentID send signal SIG_TEST to child\n", getpid());
    if (kill(pid, SIG_TEST) < 0 ){
      printf(1, "error in kill syscall\n");
    }
    printf(1, "parent waits to the child to exit\n");
    wait_ret_value = wait();

    printf(1, "parent's pid is : %d, child's pid is: %d, wait returned value is pid no. : %d\n", getpid(), pid, wait_ret_value );
    printf(1, "parent exits\n");
  }
  exit();
}
