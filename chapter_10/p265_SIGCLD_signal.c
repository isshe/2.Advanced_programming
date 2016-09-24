/*==============================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p265_SIGCLD_signal.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/01/05
* Description  : 不能正常工作的System V SIGCLD处理函数
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"
#include <sys/wait.h>

static void sig_cld(int);

int
main(void)
{
    pid_t   pid;

    printf("parent pid = %d\n", getpid());

    if (signal(SIGCLD, sig_cld) == SIG_ERR)
    {
         perror("signal error");
    }

    if ((pid = fork()) < 0)
    {
        perror("fork error");
    }
    else if ( pid == 0 )
    {
         sleep(2);
         _exit(0);      //退出的时候， 发送信号。
    }

    pause();        //parent
    exit(0);
}

static void
sig_cld(int signo)              //interrupts pause()
{
     pid_t  pid;
     int    status;

     printf("SIGCLD received\n");

     if (signal(SIGCLD, sig_cld) == SIG_ERR)        //reestablish handler
     {
          perror("signal error");
     }

     if ((pid = wait(&status)) < 0)
     {
         perror("wait error");
     }

     printf("pid = %d\n", pid);
}
