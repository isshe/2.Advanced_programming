/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p82_access.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/11/13
* Description  : access函数的使用方法;
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/


#include "apue.h"
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        err_quit("usage: a.out <pathname>");
    }

    if (access(argv[1], R_OK) < 0)
    {
         err_ret("access error for %s", argv[1]);
    }
    else
    {
        printf("read access OK\n");
    }

    if (open(argv[1], O_RDONLY) < 0)
    {
        err_ret("open error for %s", argv[1]);
    }
    else
    {
        printf("open for reading OK\n");
    }

    exit(0);
}
