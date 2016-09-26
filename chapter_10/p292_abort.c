/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p292_abort.c
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
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void abort(void)
{
     sigset_t   mask;
     struct sigaction action;

     sigaction(SIGABRT, NULL, &action);     //保存到action
     if (action.sa_handler == SIG_IGN)
     {
          action.sa_handler = SIG_DEF;
          sigaction(SIGABRT, &action, NULL);
     }

     if (action.sa_handler == SIG_DEF)
     {
          fflush(NULL);         //flush all open stdio stream
     }

     //调用者不能阻塞SIGBART
     sigfillset(&mask);
     sigdelset(&mask, SIGABRT);     //从屏蔽集中去掉
     sigprocmask(SIG_SETMASK, &mask, NULL);
     kill(getpid(), SIGABRT);       //给自己发送ISGABRT

     //一般来说应该到不了下面
     //以下代码是实现冗余吗？
     fflush(NULL);
     action.sa_handler = SIG_DEF;
     sigaction(SIGABRT, &action, NULL); //设为默认
     sigprocmask(SIG_SETMASK, &mask, NULL);
     kill(getpid(), SIGABRT);       //为何？
     exit(1);
}
