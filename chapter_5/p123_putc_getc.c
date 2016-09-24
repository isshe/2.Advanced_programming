/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p123_putc_getc.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/12/27
* Description  : 将标准输入复制到标准输出
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/


#include "apue.h"

int main(void)
{
    int     c = 0;

    while ((c = getc(stdin)) != EOF)
    {
        if(putc(c, stdout) == EOF)
        {
            err_sys("output error");
        }
    }

    if (ferror(stdin))
    {
         err_sys("input error");
    }

    exit(0);
}
