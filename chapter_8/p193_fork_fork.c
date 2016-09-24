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



     if ((pid = fork()) < 0)
     {
          err_sys("fork error");
     }
     else if (pid == 0)         //first child
     {
         if ((pid = fork()) < 0)
         {
             err_sys("fork error");
         }
         else if (pid > 0)      //第一个子进程，结束？？？
         {
             printf("first child = %ld, parent pid = %ld\n", (long)getpid(), (long)getppid());
//            if (waitpid(pid, NULL, 0) != pid) 
//            {
//                err_sys("waitpid error");
 //           }
              exit(0);
         }

 //        system("ps -al");
         sleep(2);
         printf("second child = %ld, parent pid = %ld\n", (long)getpid, (long)getppid());
         exit(0);
     }
     else
     {
        printf("parent = %ld, parent's pid = %ld\n", (long)getpid(), (long)getppid());
     }

     if (waitpid(pid, NULL, 0) != pid)  //wait for the first child !!!
     {
          err_sys("waitpid error");
     }

     exit(0);
}
