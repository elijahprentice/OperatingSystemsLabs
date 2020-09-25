#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>

#define   MAX_COUNT  30

void  ChildProcess(void);                /* child process prototype  */

void  main(void)
{

     int status;
     
     //create the first child
     int pids[2];
     pids[0] = fork();
     srand(getpid());
     
     if (pids[0] == 0){
       
       //call ChildProcess() for the first child
       ChildProcess();
       
     } else {
       
       //create the second child
       pids[1] = fork();
       
       if (pids[1] == 0){
         
         //call ChildProcess() for the second child
         ChildProcess();
         
       } else {
         
         //call ParentProcess() and wait for the child processes
         int i;
            for(i = 0; i < 2; i++){
               
               wait(&status);
               printf("Child Pid: %d has completed.\n", pids[i]);
            }
       }
     }
}

void  ChildProcess(void)
{
  
  //the child goes to sleep for a random number of times between 1 and 30
  int i;
  for (i > 0; i < (rand() % MAX_COUNT + 1); i--){
    
    //the child sleeps for a random amout of time between 1 and 10 seconds
    printf("Child Pid: %d is going to sleep!\n", getpid());
    sleep(rand() % 10 + 1);
    
    //the child wakes up and calls for their parent
    printf("Child Pid: %d is awake!\nWhere is my parent: %d?\n", getpid(),getppid());
  }
  
  exit(0);    //terminate the child process
}
