/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : stdin_out_p7.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/09/01
* Description  : 将标准输入复制到标准输出
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"

#define     BUFFSIZE        4096

int
main(int argc, char **argv)
{
    int     n = 0;
    char    buf[BUFFSIZE] = {0};

    while ( (n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0 )
    {
         if (write(STDOUT_FILENO, buf, n) != n)
         {
             err_sys("write error");
         }
    }

    if (n < 0)
    {
         err_sys("read error");
    }

    exit(0);
}
