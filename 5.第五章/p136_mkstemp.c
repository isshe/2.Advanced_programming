/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p136_mkstemp.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/12/27
* Description  : mkstemp函数的使用
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/


#include "apue.h"


void make_temp(char *template);


int
main(void)
{
    char    good_template[] = "/tmp/dirXXXXXX";
    char    *bad_template = "/tmp/dirXXXXXX";

    printf("trying to create first temp file...\n");
    make_temp(good_template);

    printf("trying to create second temp file...\n");
    make_temp(bad_template);

    exit(0);
}

void
make_temp(char *template)
{
    int     fd = 0;
    struct  stat    sbuf ;

    if ((fd = mkstemp(template)) < 0)
    {
        err_sys("mkstemp error");
    }
    printf("temp name = %s\n", template);
    close(fd);

    if (stat(template, &sbuf) < 0)
    {
         if (errno == ENOENT)
         {
             printf("file doesn't exist\n");
         }
         else
         {
             err_sys("stat error");
         }
    }
    else
    {
         printf("file exists\n");
         unlink(template);
    }
}
