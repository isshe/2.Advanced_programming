/*==============================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p286_sigsuspend.c
* Version      : v1.0.0
* Author       : i.sshe
* Date         : 2016/01/09
* Description  : 显示了保护代码临界区, 使其不被特定信号中断的正确方法
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"

static void sig_int(int);

int
main(void)
{
    sigset_t    newmask;
    sigset_t    oldmask;
    sigset_t    waitmask;

    pr_mask("program start: ");

    if (signal(SIGINT, sig_int) == SIG_ERR)
    {
         err_sys("signal(SIGINT) error");
    }

    //这些函数都不熟, 第二遍要弄熟!
    sigemptyset(&waitmask);             //清空
    sigaddset(&waitmask, SIGUSR1);      //添加SIGUSR1
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);

    //block SIGINT and save current signal mask
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
    {
         err_sys("SIG_BLOCK error");
    }

    //Critical region of code
    pr_mask("in critical region: ");

    //pause, allowing all signals except SIGUSR1
    if (sigsuspend(&waitmask) != -1)        //note!
    {
         err_sys("sigsuspend error");
    }

    pr_mask("after return form sigsuspend: ");

    //reset signal mask which unblocks SIGINT
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    {
         err_sys("SIG_SETMASK error");
    }

    //and continue processing
    pr_mask("program exit: ");

    exit(0);

}

static void
sig_int(int signo)
{
    pr_mask("\nin sig_int: ");
}
