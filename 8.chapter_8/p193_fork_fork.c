/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p193_fork_fork.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/12/31
* Description  : fork两次, 以避免僵死进程
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"
#include <sys/wait.h>
#include <stdlib.h>

int
main(void)
{
     pid_t  pid;


     printf("parent, parent's pid = %ld\n", (long)getppid());
     printf("parent, parent pid = %ld\n", (long)getpid());
     if ((pid = fork()) < 0)
     {
          err_sys("fork error");
     }
     else if (pid == 0)
     {
         if ((pid = fork()) < 0)
         {
             err_sys("fork error");
         }
         else if (pid > 0)      //第一个子进程，结束？？？
         {
             printf("first child, parent pid = %ld\n", (long)getppid());
             printf("first child exit!\n");
              exit(0);
         }

 //        system("ps -al");
         sleep(2);
         printf("second child, parent pid = %ld\n", (long)getppid());
         exit(0);
     }

     if (waitpid(pid, NULL, 0) != pid)  //wait for the first child !!!
     {
          err_sys("waitpid error");
     }

     exit(0);
}
