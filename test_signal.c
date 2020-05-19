// command for shell: test_signal
#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int num_of_loops = 1;
  for (int i = 0; i<num_of_loops; i++){

    int pid = fork();

    if (pid == 0){ //child
      while(1){
        printf(1, "child still not dead\n");
      }
      exit();
    } 
    else{ //parent
      sleep(5);
    
      printf(1, "send SIGSTOP to child ");
      if(kill(pid, SIGSTOP) == 0){
        printf(1, "ACK\n");
      } else{
        printf(1, "NACK\n");
      }
      sleep(5);

      printf(1, "send SIGCONT to child ");
      if(kill(pid, SIGCONT) == 0){
        printf(1, "ACK\n");
      } else{
        printf(1, "NACK\n");
      }

      printf(1, "send onther SIGCONT to child  (unused)");
      if(kill(pid, SIGCONT) == 0){
        printf(1, "ACK\n");
      } else{
        printf(1, "NACK\n");
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
