/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p289_5syn_func.c
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

static volatile sig_atomic_t sigflag;
static sigset_t newmask;
static sigset_t oldmask;
static sigset_t zeromask;

static void
sig_usr(int signo)
{
     sigflag = 1;
}

void
TELL_WAIT(void)
{
     if (signal(SIGUSR1, sig_usr) == SIG_ERR)
     {
         err_sys("signal(SIGUSR1) error");
     }

     if (signal(SIGUSR2, sig_usr) == SIG_ERR)
     {
          err_sys("signal(SIGUSR2) error");
     }

     sigemptyset(&zeromask);
     sigemptyset(&newmask);
     sigaddset(&newmask, SIGUSR1);
     sigaddset(&newmask, SIGUSR2);

     if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
     {
          err_sys("SIG_BLOCK error");
     }

}

void
TELL_PARENT(pid_t pid)
{
     kill(pid, SIGUSR2);
}

void
WAIT_PARENT(void)
{
     while(sigflag == 0)
     {
         sigsuspend(&zeromask);         //阻塞
     }
     sigflag = 0;

     //重置屏蔽信号集
     if (sigprocmask(SIG_SETMASK, &oldmask, NULL) <0)
     {
          sys_err("SIG_SETMASK error");
     }
}

void
TELL_CHILD(pid_t pid)
{
     kill(pid, SIGUSR1);
}

void
WAIT_CHILD(void)
{
     while(sigflag == 0)
     {
         sigsuspend(&zeromask); //这里并没有阻塞两个用户信号
     }
     sigflag = 0;

     if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
     {
          err_sys("SIG_SETMASK error");
     }
}
