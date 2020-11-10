// C program for implementation of Simulation 
#include<stdio.h> 
#include<limits.h>
#include<stdlib.h>
#include "process.h"
#include "util.h"


// Function to find the waiting time for all  
// processes
void findWaitingTimeRR(ProcessType plist[], int n,int quantum) 
{ 
  
  /*
     1. Create an array *rem_bt[]* to keep track of remaining burst time of processes. This array is initially a copy of *plist[].bt* (all processes burst times)
     2. Store waiting times of processes in plist[].wt. Initialize this array as 0.
     3. Initialize time : t = 0
     4. Keep traversing the all processes while all processes are not done. Do following for i'th process if it is not done yet.
        - If rem_bt[i] > quantum
          (i)  t = t + quantum
          (ii) bt_rem[i] -= quantum;
        - Else // Last cycle for this process
          (i)  t = t + bt_rem[i];
          (ii) plist[i].wt = t - plist[i].bt
          (iii) bt_rem[i] = 0; // This process is over
       
   */
  
  int rem_bt[n];     // array of all burst times
  int t = 0;         // time
  int i, k;          // i: storing burst times, k: loop through all flags
  int done[n];       // flag to check if each process is done
  int all_done = 1;  // flag to check if all processes are done
  for (i = 0; i < n; i++) {
    rem_bt[i] = plist[i].bt;     // storing remaining burst times
    plist[i].wt = 0;             // initializing wait times as 0
    done[i] = 0;                 // initializing processes to not be done
  }
  
  for (i = 0; i < n; i++) {
    
    if (done[i] == 0) {
      
      if (rem_bt[i] > quantum) {
        t += quantum;
        rem_bt[i] -= quantum;
      } else {
        t += rem_bt[i];
        plist[i].wt = t - plist[i].bt;
        rem_bt[i] = 0;
        done[i] = 1; //process is finished
      }
    }
    
    if ((n-1) == i) {
      
      for (k = 0; k < n; k++) {
        
        if (done[k] == 0) {
          all_done = 0;
        } 
      }
      if (all_done == 0) {
        i = -1;
        all_done = 1;
      }
    }
  }
}


// Sorting integer array
// https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm
int cmp(const void * a, const void * b)
{
  return(*(int*)a - *(int*)b);
}
// Function to find the waiting time for all  
// processes 
void findWaitingTimeSJF(ProcessType plist[], int n)
{ 
      /*
       * 1 Traverse until all process gets completely executed.
         - Find process with minimum remaining time at every single time lap.
         - Reduce its time by 1.
         - Check if its remaining time becomes 0 
         - Increment the counter of process completion.
         - Completion time of *current process = current_time +1;*
         - Calculate waiting time for each completed process. *wt[i]= Completion time - arrival_time-burst_time*
         - Increment time lap by one.
 
     */
  
  /*
   * schedsim_ref input1.txt should give wait times 3,16,9,0
   * like the example in the CPU scheduling Powerpoint, but it
   * prints out 3,16,8,0.
   */
  int bt_times[n];  //array of all burst times
  int i, k;
  for (i = 0; i < n; i++) {
    bt_times[i] = plist[i].bt;   //storing burst times
  }
  qsort(bt_times, n, sizeof(int), cmp);   //sorting burst times
  
  int current_time = 0;
  for (i = 0; i < n; i++) {
    
    for (k = 0; k < n; k++) {
      
      if (bt_times[i] == plist[k].bt) {
        plist[k].wt = current_time;
        current_time += bt_times[i];
        break;
      }
    }
  }
} 

// Function to find the waiting time for all  
// processes 
void findWaitingTime(ProcessType plist[], int n)
{ 
    // waiting time for first process is 0, or the arrival time if not 
    plist[0].wt = 0 +  plist[0].art; 
  
    // calculating waiting time 
    for (int  i = 1; i < n ; i++ ) 
        plist[i].wt =  plist[i-1].bt + plist[i-1].wt; 
} 
  
// Function to calculate turn around time 
void findTurnAroundTime( ProcessType plist[], int n)
{ 
    // calculating turnaround time by adding bt[i] + wt[i] 
    for (int  i = 0; i < n ; i++) 
        plist[i].tat = plist[i].bt + plist[i].wt; 
} 
  
// Function to sort the Process acc. to priority
int my_comparer(const void *this, const void *that)
{ 
  
    /*  
     * 1. Cast this and that into (ProcessType *)
     * 2. return 1 if this->pri < that->pri
     */ 
    ProcessType * this_proc = (ProcessType *) this;
    ProcessType * that_proc = (ProcessType *) that;

    return (this_proc->pri < that_proc->pri);
} 

//Function to calculate average time 
void findavgTimeFCFS( ProcessType plist[], int n) 
{ 
    //Function to find waiting time of all processes 
    findWaitingTime(plist, n); 
  
    //Function to find turn around time for all processes 
    findTurnAroundTime(plist, n); 
  
    //Display processes along with all details 
    printf("\n*********\nFCFS\n");
}

//Function to calculate average time 
void findavgTimeSJF( ProcessType plist[], int n) 
{ 
    //Function to find waiting time of all processes 
    findWaitingTimeSJF(plist, n); 
  
    //Function to find turn around time for all processes 
    findTurnAroundTime(plist, n); 
  
    //Display processes along with all details 
    printf("\n*********\nSJF\n");
}

//Function to calculate average time 
void findavgTimeRR( ProcessType plist[], int n, int quantum) 
{ 
    //Function to find waiting time of all processes 
    findWaitingTimeRR(plist, n, quantum); 
  
    //Function to find turn around time for all processes 
    findTurnAroundTime(plist, n); 
  
    //Display processes along with all details 
    printf("\n*********\nRR Quantum = %d\n", quantum);
}

//Function to calculate average time 
void findavgTimePriority( ProcessType plist[], int n) 
{ 
  
   /*
    * 1- Sort the processes (i.e. plist[]), burst time and priority according to the priority.
    * 2- Now simply apply FCFS algorithm.
    */
    
    // Managed to get qsort to work
    qsort(plist, n, sizeof(ProcessType), my_comparer);
  
    /*
    // Bubble sort processes: 'qsort' was not working
    // for me, so I'm using a bubble sort algorithm as
    // a placeholder until I figure out the issue.
    int temp, k, i;
    int swapped = 0;
    for (k = 0; k < (n - 1); k++) {
      
      for (i = 0; i < (n - k - 1); i++) {
        
        if (plist[i].pri < plist[i+1].pri) {
          
          // Swap priorities
          temp = plist[i].pri;
          plist[i].pri = plist[i+1].pri;
          plist[i+1].pri = temp;
          
          // Swap process IDs
          temp = plist[i].pid;
          plist[i].pid = plist[i+1].pid;
          plist[i+1].pid = temp;
          
          // Swap burst times
          temp = plist[i].bt;
          plist[i].bt = plist[i+1].bt;
          plist[i+1].bt = temp;
          
          swapped = 1;
          //printf("Swapped\n");
        }
      }
      if (swapped == 1) {
        break;
      }
    }
    

    int a = 0;
    for(; a < n; a++) {
      printf("%d\n", plist[a].pri);
    }
    */
    
    findWaitingTime(plist, n);
    findTurnAroundTime(plist, n); 
    
  
    //Display processes along with all details 
    printf("\n*********\nPriority\n");
}

void printMetrics(ProcessType plist[], int n)
{
    int total_wt = 0, total_tat = 0; 
    float awt, att;
    
    printf("\tProcesses\tBurst time\tWaiting time\tTurn around time\n"); 
  
    // Calculate total waiting time and total turn  
    // around time 
    for (int  i=0; i<n; i++) 
    { 
        total_wt = total_wt + plist[i].wt; 
        total_tat = total_tat + plist[i].tat; 
        printf("\t%d\t\t%d\t\t%d\t\t%d\n", plist[i].pid, plist[i].bt, plist[i].wt, plist[i].tat); 
    } 
  
    awt = ((float)total_wt / (float)n);
    att = ((float)total_tat / (float)n);
    
    printf("\nAverage waiting time = %.2f", awt); 
    printf("\nAverage turn around time = %.2f\n", att); 
} 

ProcessType * initProc(char *filename, int *n) 
{
  	FILE *input_file = fopen(filename, "r");
	  if (!input_file) {
		    fprintf(stderr, "Error: Invalid filepath\n");
		    fflush(stdout);
		    exit(0);
	  }

    ProcessType *plist = parse_file(input_file, n);
  
    fclose(input_file);
  
    return plist;
}
  
// Driver code 
int main(int argc, char *argv[]) 
{ 
    int n; 
    int quantum = 2;

    ProcessType *proc_list;
  
    if (argc < 2) {
		   fprintf(stderr, "Usage: ./schedsim <input-file-path>\n");
		   fflush(stdout);
		   return 1;
	   }
    
  // FCFS
    n = 0;
    proc_list = initProc(argv[1], &n);
  
    findavgTimeFCFS(proc_list, n);
    
    printMetrics(proc_list, n);
  
  // SJF
    n = 0;
    proc_list = initProc(argv[1], &n);
   
    findavgTimeSJF(proc_list, n); 
   
    printMetrics(proc_list, n);
  
  // Priority
    n = 0; 
    proc_list = initProc(argv[1], &n);
    
    findavgTimePriority(proc_list, n); 
    
    printMetrics(proc_list, n);
    
  // RR
    n = 0;
    proc_list = initProc(argv[1], &n);
    
    findavgTimeRR(proc_list, n, quantum); 
    
    printMetrics(proc_list, n);
    
    return 0; 
} 