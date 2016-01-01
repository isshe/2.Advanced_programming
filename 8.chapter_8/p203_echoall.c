/*==============================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p203_echoall.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/01/01
* Description  : echoall ,显示所有命令行参数和所有环境字符串
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/


#include "apue.h"

int
main(int argc, char *argv[])
{
     int    i = 0;
     char   **ptr = NULL;
     extern char    **environ;

     for (i = 0; i < argc; i++)
     {
          printf("argv[%d]: %s\n", i, argv[i]);
     }

     for (ptr = environ; *ptr != 0; ptr++)
     {
          printf("%s\n", *ptr);
     }

     exit(0);
}
