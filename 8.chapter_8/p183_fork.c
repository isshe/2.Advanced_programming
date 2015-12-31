/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p183_fork.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/12/31
* Description  : fork函数实例
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/


#include "apue.h"

int     globval = 6;
char    buf[] = "a write to stdout\n";

int
main(void)
{
     int    var = 0;
     pid_t  pid;

     var = 88;
     if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
     {
          err_sys("write error");
     }

     printf("before fork\n");   //we don't flush stdout
     if ((pid = fork()) < 0)
     {
          err_sys("fork error");
     }
     else if (pid == 0)
     {
          globval++;
          var++;
     }
     else
     {
          sleep(2);
     }

     printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globval, var);

     exit(0);
}
