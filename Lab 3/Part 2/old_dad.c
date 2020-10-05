#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

#define  MAX_SLEEP     5
#define  MAX_DEPOSIT   100
#define  STUDENT_NEED  50

void DearOldDad(int*, int*);
void Deposit(int*, int*);
void PoorStudent(int*, int*);

int main(int  argc, char *argv[])
{
  int BankAccount;
  int *BankPTR;
  int Turn;
  int *TurnPTR;
  
  pid_t pid;
  int status;
  
  BankAccount = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
  Turn = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
  if ((BankAccount < 0) || (Turn < 0)){
    printf("*** shmget error (server) ***\n");
    exit(1);
  }
  
  BankPTR = (int *) shmat(BankAccount, NULL, 0);
  TurnPTR = (int *) shmat(Turn, NULL, 0);
  if ((*BankPTR == -1) || (*TurnPTR == -1)){
    printf("*** shmat error (server) ***\n");
    exit(1);
  }
  
  pid = fork();
  srand(getpid());
  if (pid < 0){
    
    printf("*** fork error (server) ***\n");
    exit(1);
  } else if (pid == 0){
    
    PoorStudent(BankPTR, TurnPTR);
    exit(0);
  } else {
    
    DearOldDad(BankPTR, TurnPTR);
    wait(&status);
    exit(0);
  }
  
  exit(0);
}

void DearOldDad(int * PtrBank, int * PtrTurn)
{
  int i;
    for (i = 0; i < 15; i++){
    sleep(rand() % MAX_SLEEP);
  
    while(*PtrTurn != 0){}
  
    if(*PtrBank <= 100){
      Deposit(PtrBank, PtrTurn);
    } else {
      printf("Dear old Dad: Thinks Student has enough Cash ($%d)\n", *PtrBank);
    }
    *PtrTurn = 1;
  }
}

void Deposit(int * PtrBank, int * PtrTurn)
{
  int balance = rand() % MAX_DEPOSIT;
  
  if ((balance % 2) == 0){
    *PtrBank += balance;
    printf("Dear old Dad: Deposits $%d / Balance = $%d\n", balance, *PtrBank);
  } else {
    printf("Dear old Dad: Doesn't have any money to give\n");
  }
  
  *PtrTurn = 1;
}

void PoorStudent(int * PtrBank, int * PtrTurn)
{
  
  int j;
  for(j = 0; j < 15; j++){
  
    sleep(rand() % MAX_SLEEP);
  
    while(*PtrTurn != 1){}
  
    int balance = rand() % STUDENT_NEED;
    printf("Poor Student needs $%d\n", balance);
  
    if (balance <= *PtrBank)
    {
      *PtrBank -= balance;
      printf("Poor Student: Withdraws $%d / Balance = $%d\n", balance, *PtrBank);
    } else {
      printf("Poor Student: Not Enough Cash ($%d)\n", *PtrBank);
    }
    *PtrTurn = 0;
  }
}