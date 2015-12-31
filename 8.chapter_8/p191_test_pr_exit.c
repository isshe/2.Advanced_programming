/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p191_test_pr_exit.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/12/31
* Description  : 调用pr_exit函数， 演示终止状态的各种值
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"
#include <sys/wait.h>

void pr_exit(int status);

int
main(void)
{
     pid_t  pid;
     int    status = 0;

     if ((pid = fork()) < 0)
     {
          err_sys("fork error");
     }
     else if (pid == 0)
     {
          exit(7);
     }

     if (wait(&status) != pid)
     {
          err_sys("wait error");
     }
     pr_exit(status);

     if ((pid = fork()) < 0)
     {
          err_sys("fork error");
     }
     else if (pid == 0)
     {
          abort();          //generates SIGABRT
     }

     if (wait(&status) != pid)
     {
         err_sys("wait error");
     }
     pr_exit(status);

     if ((pid = fork()) < 0)
     {
          err_sys("fork error");
     }
     else if (pid == 0)
     {
          status /= 0;
     }

     if (wait(&status) != pid)
     {
          err_sys("wait error");
     }
     pr_exit(status);

     exit(0);
}
