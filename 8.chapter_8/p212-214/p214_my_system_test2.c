/*==============================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p214_my_system_test2.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/01/02
* Description  : 用my_system执行命令行参数
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"

int my_system(const char *cmdstring);

void pr_exit(int status);


int
main(int argc, char *argv[])
{
    int     status = 0;

    if (argc < 2)
    {
        err_quit("command-line argument required");
    }

    if ((status = my_system(argv[1])) < 0)
    {
         err_sys("my_system error");
    }

    pr_exit(status);

    exit(0);
}
