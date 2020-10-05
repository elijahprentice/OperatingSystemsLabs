#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <sys/wait.h> 
#include <stdlib.h>

int main(int argc, char **argv)
{
  
  /*
   * these links helped me gain a better understanding of
   * pipes and how to use dup2 with STDIN_FILENO and STDOUT_FILENO
   * https://linuxhint.com/dup2_system_call_c/
   * http://www.rozmichelle.com/pipes-forks-dups/
  */
  
  int pipefd[2];
  int pipefd2[2];
  int pid;
  
  int status;

  char *cat_args[] = {"cat", "scores", NULL};
  char *grep_args[] = {"grep", argv[1], NULL};
  
  char *sort_args[] = {"sort"};

  // make a pipe (fds go in pipefd[0] and pipefd[1])

  pipe(pipefd);
  pipe(pipefd2);

  pid = fork();

  if (pid == 0)
    {
      // child gets here and handles "grep Villanova"

      // replace standard input with input part of pipe

      dup2(pipefd[0], STDIN_FILENO);
      dup2(pipefd2[1], STDOUT_FILENO);

      // close unused output half of pipe

      close(pipefd[1]);
      close(pipefd2[0]);

      // execute grep

      execvp("grep", grep_args);
      exit(0);
    }
  else
    {
      pid = fork();
      
      if(pid == 0)
      {
        
        dup2(pipefd2[0], STDIN_FILENO);
        
        close(pipefd[1]);
        close(pipefd[0]);
        close(pipefd2[1]);
        
        execvp("sort", sort_args);
        exit(0);
      } else {
        
        // parent gets here and handles "cat scores"

        // replace standard output with output part of pipe

        dup2(pipefd[1], STDOUT_FILENO);

        // close unused input half of pipe

        close(pipefd[0]);
        close(pipefd2[0]);
        close(pipefd2[1]);

        // execute cat

        execvp("cat", cat_args);
        wait(&status);
        wait(&status);
        exit(0);
        }
    }
  exit(0);
}