/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p109_chdir.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/12/27
* Description  : chdir 改变工作目录
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"

int main(void)
{
    if (chdir("/tmp") < 0)
    {
        err_sys("chdir failed");
    }

    printf("chdir to /tmp succeeded\n");

    exit(0);
}
