/*==============================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p202_execle_execlp.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/01/01
* Description  : exec函数实例，它显示所有命令行参数及全部环境表。
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"
#include <sys/wait.h>

char *env_init[] = { "USER=unknown", "PATH=/tmp", NULL };

int
main(void)
{
     pid_t  pid;

     if ((pid = fork()) < 0)
     {
          err_sys("fork error");
     }
     else if (pid == 0)
     {
          if (execle("/home/isshe/1.code/2.Advanced_programming/8.chapter_8/echoall", "echoall", "myarg1", "MY ARG2",
                      (char *)0, env_init) < 0)
          {
              err_sys("execle error");
          }

     }

     if (waitpid(pid, NULL, 0) < 0)
     {
          err_sys("wait error");
     }

     if ((pid = fork()) < 0)
     {
          err_sys("fork error");
     }
     else if (pid == 0)
     {
          if (execlp("/home/isshe/1.code/2.Advanced_programming/8.chapter_8/echoall", "echoall", "only 1 arg", (char *)0) < 0)
          {
              err_sys("execlp error");
          }
     }

     exit(0);
}
