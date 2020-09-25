#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

int sec = 0;

void alarms() {
  sec += 1;
}

void sigint_handler(int signum){
  
  printf("\nRan for %d seconds.\n", sec);
  exit(0);
}