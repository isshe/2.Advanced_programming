/*==============================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p275_print_signal_name.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/01/06
* Description  : 打印调用进程信号屏蔽字中的信号字, p284,p287的程序会调用此程序
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"
#include <errno.h>

void
pr_mask(const char *str)
{
    sigset_t    sigset;
    int         errno_save = 0;

    errno = errno;
    if (sigprocmask(0, NULL, &sigset) < 0)
    {
         err_ret("sigprocmask error");
    }
    else
    {
        printf("%s", str);

        if (sigismember(&sigset, SIGINT))
        {
             printf(" SIGINT");
        }

        if (sigismember(&sigset, SIGQUIT))
        {
            printf(" SIGQUIT");
        }

        if (sigismember(&sigset, SIGUSR1))
        {
             printf(" SIGUSR1");
        }

        if (sigismember(&sigset, SIGUSR2))
        {
            printf(" SIGUSR2");
        }

        printf("\n");
    }

    errno = errno_save;
}

/*
int
main(void)
{
     pr_mask("isshe");

     return 0;
}
*/
