/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p161_atexit.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/12/28
* Description  : 终止处理程序实例， atexit的用法
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"

static void     my_exit1(void);
static void     my_exit2(void);

int
main(void)
{
    if (atexit(my_exit2) != 0)
    {
        err_sys("can't register my_exit2");
    }

    if (atexit(my_exit1) != 0)
    {
         err_sys("can't register my_exit1");
    }
    if (atexit(my_exit1) != 0)
    {
        err_sys("can't register my_exit1");
    }

    printf("main is done!\n");

    exit(0);
}


static void
my_exit1(void)
{
     printf("first exit handler\n");
}

static void
my_exit2(void)
{
    printf("second exit handler\n");
}
