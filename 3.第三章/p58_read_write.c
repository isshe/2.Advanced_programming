/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p58_read_write.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/11/10
* Description  :
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"

#define BUFFSIZE    4096

int main(void)
{
    int     n = 0;
    char    buf[BUFFSIZE];

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
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
