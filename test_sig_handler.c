// command for shell: test_sig_handler
#include "types.h"
#include "stat.h"
#include "user.h"
#define SIG_TEST 7
volatile int keep_running = 1;
////////TODO: romove
#define SIG_IGN 1
#define SIG20 20
#define SIG21 21
#define SIG22 22
#define SIG23 23
#define SIG24 24
////////

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

////////////////////////////////////////////////////////////
//TODO: remove these tests:

int flag=1;
void userSignal1(int signum)
{
    flag=0;
}
void userSignal2(int signum)
{
    flag=1;
}
void userSignal3(int signum)
{
    flag=2;
}
void userSignal4(int signum)
{
    while(1){
    printf(1, "");
    }
}

void userSignal5(int signum)
{
    printf(1, "no print");

}
void testkill1(){
    int pid;
    if((pid=fork())==0){
        while(1){
            printf(1, "child running\n ");
        }
        exit();
    }
    else{
        sleep(10);
        printf(1,"KILL\n");
        kill(pid, SIGKILL);
        wait();
        printf(1,"testkill1- pass\n");
    }

}

void testkill2(){
    int pid;
    if((pid=fork())==0){
        while(1){
            printf(1, "child running\n ");
        }
        exit();
    }
    else{
        sleep(20);
        printf(1,"STOP\n");
        kill(pid, SIGSTOP);
        sleep(80);
        printf(1,"KILL\n");
        kill(pid, SIGKILL);
        wait();
        printf(1,"testkill2- pass\n");
    }

}

void testkill3(){
    int pid;
    if((pid=fork())==0){
        while(1){
            printf(1, "child running\n ");
        }
        exit();
    }
    else{
        sleep(20);
        printf(1,"STOP\n");
        kill(pid, SIGSTOP);
        sleep(80);
        printf(1,"KILL\n");
        kill(pid, SIG20);
        wait();
        printf(1,"testkill3- pass\n");
    }

}

void testkill4(){
    int pid;
    if((pid=fork())==0){
        while(1){
            printf(1, "child running\n ");
        }
        exit();
    }
    else{
        sleep(10);
        printf(1,"KILL\n");
        kill(pid, SIG20);
        wait();
        printf(1,"testkill4- pass\n");
    }

}

void teststopandcont1(){
     int pid;
    if((pid=fork())==0){
        while(1){
            printf(1, "child running\n ");
        }
        exit();
    }
    else{
        sleep(20);
        printf(1,"STOP\n");
        kill(pid, SIGSTOP);
        sleep(80);
        printf(1,"CONTINUE\n");
        kill(pid, SIGCONT);
        sleep(20);
        printf(1,"KILL\n");
        kill(pid, SIGKILL);
        wait();
        printf(1,"teststopandcont1- pass\n");
    } 
}



void testignure1(){
    int pid;
    if((pid=fork())==0){
        struct sigaction *act= malloc(sizeof(struct sigaction));
        act->sa_handler= (void*)SIG_IGN;
        act->sigmask=0;
        sigaction(SIGCONT,act ,null);
        while(1){
            printf(1, "child running\n ");
        }
        exit();
    }
    else{
        sleep(10);
        printf(1,"STOP\n");
        kill(pid, SIGSTOP);
        sleep(80);
        printf(1,"CONTINUE-IGNURE\n");
        kill(pid, SIGCONT);
        sleep(10);
        printf(1,"KILL\n");
        kill(pid, SIGKILL);
        wait();
        printf(1,"testusersignal1 - pass\n");
    }
}

void testusersignal1(){
    int pid;
    if((pid=fork())==0){
        struct sigaction *act= malloc(sizeof(struct sigaction));
        act->sa_handler= &userSignal1;
        act->sigmask=0;
        sigaction(SIG20,act ,null);
        while(flag){
            printf(1, "child running\n ");
        }
        exit();
    }
    else{
        sleep(10);
        printf(1,"STOP AND END\n");
        kill(pid, SIG20);
        wait();
        printf(1,"testusersignal1 - pass\n");
    }
}


void testusersignal2(){
    int pid;
    if((pid=fork())==0){
        struct sigaction *act= malloc(sizeof(struct sigaction));
        act->sa_handler= &userSignal1;
        act->sigmask=0;
        sigaction(SIGCONT,act ,null);
        while(flag){
            printf(1, "child running\n ");
        }
        exit();
    }
    else{
        sleep(10);
        printf(1,"STOP \n");
        kill(pid, SIGSTOP);
        sleep(80);
        printf(1,"CONTINUE ANF END \n");
        kill(pid, SIGCONT);
        wait();
        printf(1,"testusersignal2 - pass\n");
    }
}

void testusersignal3(){
    int pid;
    if((pid=fork())==0){
        struct sigaction *act1= malloc(sizeof(struct sigaction));
        act1->sa_handler= (void *)SIGSTOP;
        act1->sigmask=0;
        struct sigaction *act2= malloc(sizeof(struct sigaction));
        act2->sa_handler=(void *) SIGCONT;
        act2->sigmask=0;
        struct sigaction *act3= malloc(sizeof(struct sigaction));
        act3->sa_handler= (void *)SIGKILL;
        act3->sigmask=0;
        sigaction(SIG20,act1 ,null);
        sigaction(SIG21,act2 ,null);
        sigaction(SIG22,act3,null);
        
        while(1){
            printf(1, "child running\n ");
        }
        exit();
    }
    else{
        sleep(10);
        printf(1,"STOP \n");
        kill(pid, SIG20);
        sleep(80);
        printf(1,"CONTINUE\n");
        kill(pid, SIGCONT);
        sleep(50);
        printf(1,"KILL\n");
        kill(pid, SIG22);
        wait();
        printf(1,"testusersignal3 - pass\n");
    }
}


void testusersignal4(){
    int pid;
    if((pid=fork())==0){
        struct sigaction *oldact= malloc(sizeof(struct sigaction));
        struct sigaction *act1= malloc(sizeof(struct sigaction));
        act1->sa_handler= &userSignal1;
        act1->sigmask=0;
        sigaction(SIG20,act1, null);
        struct sigaction *act2= malloc(sizeof(struct sigaction));
        act2->sa_handler= &userSignal2;
        act2->sigmask=0;
        sigaction(SIG20,act2, oldact);
        sigaction(SIG20,oldact,null);
        
        while(flag){
            printf(1, "child running\n ");
        }
        exit();
    }
    else{
        sleep(40);
        printf(1,"END \n");
        kill(pid, SIG20);
        wait();
        printf(1,"testusersignal4 - pass\n");
    }
}

void testmask1(){
    int pid;
    if((pid=fork())==0){
        uint mask= 1<<SIG20;
        struct sigaction *act1= malloc(sizeof(struct sigaction));
        act1->sa_handler= &userSignal3;
        act1->sigmask=0;
        sigaction(SIG20,act1, null);
        struct sigaction *act2= malloc(sizeof(struct sigaction));
        act2->sa_handler= &userSignal1;
        act2->sigmask=0;
        sigaction(SIG21,act2, null);
        sigprocmask(mask);

        
        while(flag==1){
            printf(1, "flag: %d\n ",flag);
        }
        if(flag==2){
            printf(1,"testmask1-fail\n");
        }
        if(flag==0){
            printf(1,"testmask1-pass\n");
        }
        exit();
    }
    else{
        sleep(10);
        printf(1,"IGNURE \n");
        kill(pid, SIG20);
        sleep(80);
        printf(1,"STOP \n");
        kill(pid, SIG21);
        wait();
        printf(1,"testmask1-finish\n");
    }
}

void testmask2(){
    int pid;
    if((pid=fork())==0){
        struct sigaction *act1= malloc(sizeof(struct sigaction));
        act1->sa_handler= &userSignal4;
        act1->sigmask= 1<< SIG21;
        sigaction(SIG20,act1, null);
        struct sigaction *act2= malloc(sizeof(struct sigaction));
        act2->sa_handler= &userSignal5;
        act2->sigmask=0;
        sigaction(SIG21,act2, null);
        
        
        while(1){
            printf(1, "");
        }
 
        exit();
    }
    else{
        sleep(20);
        kill(pid, SIG20);
        sleep(40);
        kill(pid, SIG21);
        sleep(20);
        kill(pid, SIGKILL);
        wait();
        printf(1,"testmask2-finish\n");
    }
}
/*
int main(int argc, char *argv[])
{
    sleep(80);
    printf(1, "-----TEST SIGKILL-----\n");
    testkill1();
    printf(1, "-----------------------\n");
    testkill2();
    printf(1, "-----------------------\n");
    testkill3();
    printf(1, "-----------------------\n");
    testkill4();
    printf(1, "-----TEST SIGSTOP AND SIGCONT-----\n");
    teststopandcont1();
    printf(1, "-----------------------\n");
    printf(1, "-----TEST SIG_IGN-----\n");
    testignure1();
    printf(1, "-----------------------\n");
    printf(1, "-----TEST USER SIGNAL-----\n");
    testusersignal1();
    printf(1, "-----------------------\n");
    testusersignal2();
     printf(1, "-----------------------\n");
    testusersignal3();
    printf(1, "-----------------------\n");
    testusersignal4();
    printf(1, "-----TEST MASK-----\n");
    testmask1();
     printf(1, "-----------------------\n");
      testmask2();
    exit();
}*/
