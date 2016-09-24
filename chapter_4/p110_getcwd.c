/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p110_getpwd.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/12/27
* Description  : 获取绝对路径
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"

int main(void)
{
    char    *ptr = NULL;
    size_t  size = 128;

    if (chdir("/tmp") < 0)
    {
        err_sys("chdir failed");
    }

    ptr = malloc(sizeof(char) * size);

    if (getcwd(ptr, size) == NULL)
    {
         err_sys("getcwd failed");
    }

    printf("cwd = %s\n", ptr);

    exit(0);
}
