/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p288_sigsuspend.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/09/25
* Description  :
* Function list: 1.
*                2.
*                3.
* History      :
\*=========================================================================*/

/*-----------------------------------------------------------*
 * 头文件                                                    *
 *-----------------------------------------------------------*/
#include "apue.h"

volatile sig_atomic_t   quitflag;

static void
sig_int(int signo)
{
    if (signo == SIGINT)
    {
         printf("\ninterrupt\n");
    }
    else if (signo == SIGQUIT)
    {
        printf("quit~\n");
        quitflag = 1;
    }
}

int main(void)
{
     sigset_t newmask;
     sigset_t oldmask;
     sigset_t zeromask;

     if (signal(SIGINT, sig_int) == SIG_ERR)
     {
         err_sys("signal(SIGINT) error");
     }
     if (signal(SIGQUIT, sig_int) == SIG_ERR)
     {
          err_sys("signal(SIGQUIT) error");
     }

     sigemptyset(&zeromask);
     sigemptyset(&newmask);
     sigaddset(&newmask, SIGQUIT);
     sigaddset(&zeromask, SIGQUIT);

     //阻塞SIGQUIT并且保存当前屏蔽信号
     //两个sigprocmask函数间是代码临界区
     if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
     {
          err_sys("SIG_BLOCK error");
     }

     while (quitflag == 0)
     {
         printf("before sigsuspend\n");
//         sleep(5);
         sigsuspend(&zeromask);
     }

     quitflag = 0;
     printf("???\n");
     if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
     {
          err_sys("SIG_SETMASK error");
     }

     exit(0);
}
