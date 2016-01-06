/*==============================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p277_set_signal_sigprocmask.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/01/06
* Description  : 信号设置和sigprocmask实例
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/


#include "apue.h"

static void sig_quit(int);

int
main(void)
{
    sigset_t    newmask;
    sigset_t    oldmask;
    sigset_t    pendmask;

    if (signal(SIGQUIT, sig_quit) == SIG_ERR)
    {
         err_sys("can't catch SIGQUIT");
    }

    sigemptyset(&newmask);      //清空信号集
    sigaddset(&newmask, SIGQUIT);

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
    {
         err_sys("sigprocmask error");
    }

    sleep(5);

    if (sigpending(&pendmask) < 0)
    {
         err_sys("sigpending error");
    }
    if (sigismember(&pendmask, SIGQUIT))
    {
        printf("\nSIGQUIT pending \n");
    }

    //restore signal mask which unblocks SIGQUIT
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    {
         err_sys("SIG_SETMASK error");
    }

    printf("SIGQUIT unblocked\n");

    sleep(5);

    exit(0);
}

static void
sig_quit(int signo)
{
     printf("caught SIGQUIT\n");
     if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
     {
         err_sys("can't reset SIGQUIT");
     }
}
