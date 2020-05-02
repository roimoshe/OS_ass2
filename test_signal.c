#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int pid = fork();
  int number_of_iterations = 1000;
  if (pid == 0){ //child
    for(int i = 0; i < number_of_iterations; i++){
      printf(1, "child: %d\n", i);
    }
    exit();
  } else{ //parent
    for(int i = 0; i < number_of_iterations/2; i++){
      printf(1, "parent: %d\n", i);
    }
    kill(pid, SIGKILL);
  }
  exit();
}
