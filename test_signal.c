// command for shell: test_signal
#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  for (int i = 0; i<10; i++){
    printf(1, ">>>TEST SIGKILL<<<\n");
    int pid = fork();
    int number_of_iterations = 20;
    if (pid == 0){ //child
      for(int i = 0; i < number_of_iterations; i++){
        printf(1, "child: %d\n", i);
      }
      exit();
    } else{ //parent
      for(int i = 0; i < number_of_iterations/2; i++){
        printf(1, "parent: %d\n", i);
      }
      printf(1, "send SIGKILL to child and wait till he exits\n");
      kill(pid, SIGKILL);
      wait();
      printf(1, ">>>SIGKILL PASS<<<\n");
    }

    printf(1, ">>>TEST SIGSTOP/SIGCONT<<<\n");
    pid = fork();
    if (pid == 0){ //child
      for(int i = 0; i < number_of_iterations*100000; i++){
        printf(1, "child: %d\n", i);
      }
      exit();
    } else{ //parent
      for(int i = 0; i < number_of_iterations; i++){
        printf(1, "parent: %d\n", i);
      }
      printf(1, "send SIGSTOP to child\n");
      kill(pid, SIGSTOP);
      sleep(10);
      for(int i = number_of_iterations; i < 2*number_of_iterations; i++){
        printf(1, "parent: %d\n", i);
      }
      printf(1, "send SIGCONT to child\n");
      kill(pid, SIGCONT);
      sleep(10);
      for(int i = 2*number_of_iterations; i < 3*number_of_iterations; i++){
        printf(1, "parent: %d\n", i);
      }
      printf(1, "send SIGKILL to child (with pid %d) and wait till he exits\n", pid);
      if(kill(pid, SIGKILL) < 0){
        printf(1, "kill failed\n");
        exit();
      }
      sleep(10);
      wait();
      printf(1, ">>>SIGSTOP/SIGCONT PASS<<<\n");
    }
  }
  printf(1, ">>>!!!PASS ALL!!!<<<\n");
  exit();
}
