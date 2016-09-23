/*==============================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : my_system_test.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/01/02
* Description  : 调用my_system函数
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"
#include <sys/wait.h>

int my_system(const char *cmdstring);

void pr_exit(int status);

int
main(void)
{
    int     status = 0;

    if ((status = my_system("top")) < 0)
    {
        err_sys("my_system error");
    }

    pr_exit(status);

    if ((status = my_system("nosuchcommand")) < 0)
    {
         err_sys("my_system error");
    }

    pr_exit(status);

    if ((status = my_system("who; exit 44")) < 0)
    {
         err_sys("my_system error");
    }

    pr_exit(status);

    exit(0);
}
