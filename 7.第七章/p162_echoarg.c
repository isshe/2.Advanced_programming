/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p162_echoarg.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/12/28
* Description  : 输出命令行参数
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"

int
main(int argc, char *argv[])
{
    int     i = 0;

    for (i = 0; argv[i] != NULL; i++)
    {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    exit(0);
}
