// command for shell: test_signal
#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  for (int i = 0; i<10; i++){
    int number_of_iterations = 50;
    int pid = fork();
    if (pid == 0){ //child
      for(int i = 0; 1; i++){
        printf(1, "child: %d\n", i);
      }
      exit();
    } else{ //parent
      for(int i = 0; i < number_of_iterations; i++){
        printf(1, "parent: %d\n", i);
      }
      printf(1, "send SIGSTOP to child ");
      if(kill(pid, SIGSTOP) == 0){
        printf(1, "ACK\n");
      } else{
        printf(1, "NACK\n");
      }
      for(int i = number_of_iterations; i < 2*number_of_iterations; i++){
        printf(1, "parent: %d\n", i);
      }
      printf(1, "send SIGCONT to child ");
      if(kill(pid, SIGCONT) == 0){
        printf(1, "ACK\n");
      } else{
        printf(1, "NACK\n");
      }
      for(int i = 2*number_of_iterations; i < 4*number_of_iterations; i++){
        printf(1, "parent: %d\n", i);
      }
      printf(1, "send SIGKILL to child and wait till he exits ");
      if(kill(pid, SIGKILL) == 0){
        printf(1, "ACK\n");
      } else{
        printf(1, "NACK\n");
      }
      wait();
      printf(1, ">>>SIGSTOP/SIGCONT PASS<<<\n");
    }
  }
  printf(1, ">>>ALL PASS<<<\n");
  exit();
}
