/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : test_vsnprintf.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/08/31
* Description  : 看下vnsprintf()函数怎么用
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/


#include <stdio.h>

int max(char *a)
{
    char buf[1024];
    char *c = a;
    va_list ap ;

    vsnprintf(buf, 1023, c, ap);
    printf("buf = %s\n", buf);
    return (0);
}

int main(void)
{
    char *x = "testtesttest";
    max(x);

    return 0;
}
