/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p191_pr_exit.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/12/31
* Description  : 打印exit状态的说明， 以后很多程序会用到。所以写在一个文件中
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"
#include <sys/wait.h>

void
pr_exit(int status)
{
     if (WIFEXITED(status))
     {
         printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
     }
     else if (WIFSIGNALED(status))
     {
          printf("abnormal termination, signal number = %d%s\n",
                  WTERMSIG(status),
#ifdef  WCOREDUMP
                  WCOREDUMP(status) ? "(core file generated)" : "");
#else
                  "");
#endif
     }
     else if ( WIFSTOPPED(status) )
     {
          printf("child stopped, signal number = %d\n", WSTOPSIG(status));
     }
}
