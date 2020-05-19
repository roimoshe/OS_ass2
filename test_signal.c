// command for shell: test_signal
#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int num_of_loops = 3;
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
      kill(pid, SIGSTOP);

      sleep(5);

      kill(pid, SIGCONT);

      // send onther SIGCONT to child  (unused)
      kill(pid, SIGCONT);


      kill(pid, SIGKILL);

      wait();
      printf(1, "child still not dead\n");
      printf(1, ">>>SIGSTOP/SIGCONT PASS<<<\n");
    }
  }
  printf(1, ">>>ALL PASS<<<\n");
  exit();
}
