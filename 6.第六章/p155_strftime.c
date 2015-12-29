/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p155_strftime.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/12/29
* Description  : 使用strftime函数打印包含当前日期和时间的字符串.
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
main(void)
{
    time_t  t;
    struct  tm  *tmp;
    char    buf1[16] = {0};
    char    buf2[64];

    time(&t);
    tmp = localtime(&t);

    if (strftime(buf1, 16, "time and date: %r, %a %b %d, %Y", tmp) == 0)
    {
         printf("buffer length 16 is too small\n");
    }
    else
    {
        printf("%s\n", buf1);
    }

    if (strftime(buf2, 64, "time and date: %r, %a %b %d, %Y", tmp) == 0)
    {
         printf("buffer length 64 iss too small\n");
    }
    else
    {
        printf("%s\n", buf2);
    }

    exit(0);
}
