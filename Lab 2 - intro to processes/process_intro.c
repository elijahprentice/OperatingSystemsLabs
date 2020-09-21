#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <time.h>

#define   MAX_COUNT  30

void  ChildProcess(void);                /* child process prototype  */
void  ParentProcess(void);               /* parent process prototype */

void  main(void)
{
     pid_t  pid;

     //create the first child
     pid = fork();
     
     if (pid == 0){
       
       //call ChildProcess() for the first child
       ChildProcess();
       
     } else {
       
       //create the second child
       pid = fork();
       
       if (pid == 0){
         
         //call ChildProcess() for the second child
         ChildProcess();
         
       } else {
         
         //call ParentProcess() and wait for the child processes
         ParentProcess();
       }
     }
}

void  ChildProcess(void)
{
  
  srand(time(0));      //seed random based on time
  
  //the child goes to sleep for a random number of times between 1 and 30
  int i;
  for (i = (rand() % 30 + 1); i > 0; i--){
    
    //the child sleeps for a random amout of time between 1 and 10 seconds
    printf("Child Pid: %d is going to sleep!\n", getpid());
    sleep(rand() % 10 + 1);
    
    //the child wakes up and calls for their parent
    printf("Child Pid: %d is awake!\nWhere is my parent: %d?\n", getpid(),getppid());
  }
  
  exit(0);    //terminate the child process
}

void  ParentProcess(void)
{
  
  //parent waits for the first child process to complete
  wait(NULL);
  printf("Child Pid: %d has completed.\n", getpid());
  
  //parent waits for the second child process to complete
  wait(NULL);
  printf("Child Pid: %d has completed.\n", getpid());
}