/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : 135_tmpnam_tmpfile.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/12/27
* Description  : tmpnam 和 tmpfile函数的应用实例
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/


#include "apue.h"

int
main(void)
{
    char    name[L_tmpnam] = {0};
    char    line[L_tmpnam] = {0};
    FILE    *fp = NULL;

    printf("%s\n", tmpnam(NULL));       //first temp name

    tmpnam(name);
    printf("%s\n", name);               //second temp name

    if ((fp = tmpfile()) == NULL)
    {
         err_sys("tmefile error");
    }

    fputs("one line of output\n", fp);  //write to temp file
    rewind(fp);                         //then read it buck
    if (fgets(line, sizeof(line), fp) == NULL)
    {
         err_sys("fgets error");
    }

    fputs(line , stdout);

    exit(0);
}
