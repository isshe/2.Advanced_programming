/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p386_set_cloexec.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/11/04
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
#include <fcntl.h>

int set_closeexec(int fd)
{
    int     val = 0;

    if ((val = fcntl(fd, F_GETFD, 0)) < 0)  //获取文件描述符标志
    {
         return -1;
    }

    val |= FD_CLOEXEC;  //enable close-on-exec

    return (fcntl(fd, F_SETFD, val));
}
