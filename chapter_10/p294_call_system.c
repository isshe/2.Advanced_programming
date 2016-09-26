/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p294_system.c
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

static void
sig_int(int signo)
{
     printf("caught SIGINT\n");
}

static void
sig_chld(int signo)
{
     printf("caught SIGCHLD\n");
}

int main(void)
{
     if (signal(SIGINT, sig_int) == SIG_ERR)
     {
         err_sys("signal(SIGINT) error");
     }

     if (signal(SIGCHLD, sig_chld) == SIG_ERR)
     {
          err_sys("signal(SIGCHLD) error");
     }

     if (system("/bin/ed") < 0)
     {
          err_sys("system() error");
     }

     exit(0);
}
