/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p83_umask.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/11/13
* Description  : 创建两个文件, 第一个的umask=0;
*                第二个umask禁止所有组和其他用户的访问权限;
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"
#include <fcntl.h>

#define RWRWRW (S_IRUSR | S_IWUSR       \
                | S_IRGRP | S_IWGRP     \
                | S_IROTH | S_IWOTH)

int main(void)
{
    //第一个文件
    umask(0);
    if (creat("foo", RWRWRW) < 0)
    {
         err_sys("creat error for foo");
    }

    //第二个文件
    umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (creat("bar", RWRWRW) < 0)
    {
         err_sys("creat error for bar");
    }

    exit(0);
}

