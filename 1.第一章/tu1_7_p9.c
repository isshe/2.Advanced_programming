/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : tu1_7_p9.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/09/01
* Description  : 从标准输入读命令并执行
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/


#include "apue.h"
#include <sys/wait.h>

int
main(void)
{
    char    buf[MAXLINE] = {0};
    pid_t   pid;
    int     status;

    printf("%% ");      //print prompt (printf requires %% to print %)

    while (fgets(buf, MAXLINE, stdin) != NULL)
    {
         if (buf[strlen(buf) - 1] == '\n')
         {
             buf[strlen(buf) - 1] = 0;      //replace newline with null
         }

         if ( (pid = fork()) < 0 )
         {
              err_sys("fork error");
         }
         else if (pid == 0)         //child
         {
              //下面三行有疑问
              execlp(buf, buf, (char *)0);
              err_ret("couldn't execute: %s", buf);
              exit(127);        //???
         }

         //parent   ;;; 等待子进程结束吗???是的!
         if ( (pid = waitpid(pid, &status, 0)) < 0 )
         {
              err_sys("waitpid error");
         }
         printf("%% ");
    }

    exit(0);
}
