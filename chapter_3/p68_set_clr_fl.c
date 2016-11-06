/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p68_set_clr_fl.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/11/05
* Description  :
* Function list: 1.
*                2.
*                3.
* History      :
\*=========================================================================*/

/*-----------------------------------------------------------*
 * 头文件                                                    *
 *-----------------------------------------------------------*/
#include <fcntl.h>
#include <stdio.h>

void set_fl(int fd, int flags)
{
    int         val = 0;

    if ((val = fcntl(fd, F_GETFL, 0)) < 0)
    {
         fprintf(stderr, "fcntl F_GETFL error\n");
    }

    val |= flags;

    if (fcntl(fd, F_SETFL, val) < 0)
    {
         fprintf(stderr, "fcntl F_SETFL error\n");
    }
}


void clr_fl(int fd, int flags)
{
    int         val = 0;

    if ((val = fcntl(fd, F_GETFL, 0)) < 0)
    {
         fprintf(stderr, "fcntl F_GETFL error\n");
    }

    val &= ~flags;

    if (fcntl(fd, F_SETFL, val) < 0)
    {
         fprintf(stderr, "fcntl F_SETFL error\n");
    }
}


