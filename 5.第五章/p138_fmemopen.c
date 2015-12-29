/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p138_fmemopen.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/12/29
* Description  : 观察内存流的写入操作, 这个例子还不懂。
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"

#define     BSZ     48

int
main()
{
    FILE    *fp = NULL;
    char    buf[BSZ];

    memset(buf, 'a', BSZ-2);
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'X';
    printf("buf = %s\n", buf);
    if ((fp = fmemopen(buf, BSZ, "w+")) == NULL)
    {
         err_sys("fmemopen failed");
    }

    printf("initial buffer contents: %s\n", buf);
    fprintf(fp, "hello, world");
    printf("before flush: %s\n", buf);
    fflush(fp);
    printf("after fflush: %s\n", buf);
    printf("len of string in buf = %ld\n", (long)strlen(buf));

    memset(buf, 'b', BSZ-2);
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'X';
    printf("buf = %s\n", buf);
//    fseek(fp, 0, SEEK_SET);
    fprintf(fp, "hello, world");
    fseek(fp, 0, SEEK_SET);
    printf("after fseek: %s\n", buf);
    printf("len of string in buf = %ld\n", (long)strlen(buf));

    memset(buf, 'c', BSZ-2);
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'X';
    printf("buf = %s\n", buf);
    fprintf(fp, "hello, world");
    fclose(fp);
    printf("after fclose: %s\n", buf);
    printf("len of string in buf = %ld\n", (long)strlen(buf));

    return (0);
}
