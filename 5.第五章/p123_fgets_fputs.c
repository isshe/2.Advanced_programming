/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p123_fgets_fputs.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/12/27
* Description  : 将标准输入复制到标准输出的行版本
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/


#include "apue.h"

int main(void)
{
    char    buf[MAXLINE] = {0};

    while (fgets(buf, MAXLINE, stdin) != NULL)
    {
        if (fputs(buf, stdout) == EOF)
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
