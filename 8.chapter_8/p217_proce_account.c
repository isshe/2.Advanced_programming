/*==============================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p217_proce_account.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/01/03
* Description  : 产生会计数据的程序
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"

int
main(void)
{
     pid_t  pid;

     if ((pid = fork()) < 0)
     {
          err_sys("fork error");
     }
     else if (pid != 0)         //parent
     {
          sleep(2);
          exit(2);
     }

     if ((pid = fork()) < 0)
     {
          err_sys("fork_error");
     }
     else if (pid != 0)         //first child
     {
          sleep(4);
          abort();              //terminate with core dump
    }

     if ((pid = fork()) < 0)
     {
          err_sys("fork error");
     }
     else if (pid != 0)
     {
          execl("bin/dd", "dd", "if=/etc/passwd", "of=/dev/null", NULL);
          exit(7);
     }

     if ((pid = fork()) < 0)
     {
          err_sys("fork error");
     }
     else if (pid != 0)
     {
          sleep(8);
          exit(0);
     }

     sleep(6);
     kill(getpid(), SIGKILL);
     exit(6);
}
