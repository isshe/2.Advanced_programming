/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p15_signal.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/11/08
* Description  :
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"
#include <sys/wait.h>

static void sig_int(int);       //signal_catching Function

int main(void)
{
    char    buf[MAXLINE];      //from apue.h
    pid_t   pid;
    int     status = 0;

    if (signal(SIGINT, sig_int) == SIG_ERR)
    {
         err_sys("signal error");
    }

    printf("%% ");

    while (fgets(buf, MAXLINE, stdin) != NULL)
    {
         if (buf[strlen(buf) - 1] == '\n')
         {
             buf[strlen(buf) - 1] = '\0';
         }

         if ((pid = fork()) < 0)
         {
              err_sys("fork error");
         }
         else if ( pid == 0 )
         {
             execlp(buf, buf, (char *)0);
             err_ret("couldn't execute: %s", buf);
             exit(127);
         }

         //parent
         if ((pid = waitpid(pid, &status, 0)) < 0)
         {
              err_sys("waitpid error");
         }

         printf("%% ");
    }

    exit(0);
}

void sig_int(int signo)
{
     printf("interrupt\n%% ");
}
