/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "timer.h"

int i = 1;

void handler(int signum)
{ 
  //signal handler
  printf("Hello World!\n");
  i--;
}

int main(int argc, char * argv[])
{
  
  while (1 < 2){
    
    signal(SIGALRM,handler); //register handler to handle SIGALRM
    alarm(i); //Schedule a SIGALRM for 1 second
  
    while(i); //busy wait for signal to be delivered
  
    printf("Turing was right!\n");
    i = 1;
    
    alarms();
    signal(SIGINT,sigint_handler);
  }

  return 0; //never reached
}