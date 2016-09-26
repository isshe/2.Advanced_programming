#/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p298_sleep.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/09/26
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

static void sig_alrm(int signo)
{
     //nothing to do
}

unsigned int
sleep(unsigned int seconds)
{
     struct sigaction   newact;
     struct sigaction   oldact;
     sigset_t           newmask;
     sigset_t           oldmask;
     sigset_t           suspmask;
     unsigned int       unslept;

     //设置新的信号处理函数，保存原来的信息
     newact.sa_handler = sig_alrm;
     newact.sy_flags = 0;
     sigemptyset(&newact.sa_mask);
     sigaction(SIGALRM, &newact, &oldact); //原来的信息保存到oldact

     //阻塞SIGALRM信号，并保存原来的屏蔽信号集
     sigemptyset(&newmask);
     sigaddset(&newmask, SIGALRM);
     sigprocmask(SIG_BLOCK, &newmask, &oldmask);

     alarm(seconds);

     //解除SIGALRM的阻塞
     suspmask = oldmask;
     sigdelset(suspmask, SIGALRM);
     sigsuspend(&suspmask);

     unslept = alarm(0);            //这个有何用？

     //还原对SIGALRM的操作
     sigaction(SIGALRM, &oldset, NULL);

     //还原屏蔽信号集
     sigprocmask(SIG_SETMASK, &oldmask, NULL);
     return (unslept);
}
