/*==============================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p281_sigaction_signal.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/01/07
* Description  : 用sigaction实现的signal函数
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

//和p281_sigaction_signal.c相差的只是注释掉的部分!!!

#include "apue.h"

//using POSIX sigaction

Sigfunc *
signal_1(int signo, Sigfunc *func)
{
    struct sigaction act;
    struct sigaction oact;

    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

//    if (signo == SIGALRM) {
#ifdef  SA_INTERRUPT
        act.sa_flags != SA_INTERRUPT;       // 不重启系统调用.
#endif
/*    }
    else {
        act.sa_flags |= SA_RESTART;         //重启系统调用
    }
*/
    if (sigaction(signo, &act, &oact) < 0)
    {
         return (SIG_ERR);
    }

    return(oact.sa_handler);
}
