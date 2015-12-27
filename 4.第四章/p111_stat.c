/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p111_stat.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/12/27
* Description  : 为每个命令行参数打印设备号
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"

int main(int argc, char *argv[])
{
    int     i = 0;
    struct  stat    buf;

    for (i = 1; i < argc; i++)
    {
        printf("%s: ", argv[i]);

        if (stat(argv[i], &buf) < 0)
        {
             err_ret("stat error");
             continue;
        }

        printf("dev = %d/%d", major(buf.st_dev), minor(buf.st_dev));

        if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
        {
             printf(" (%s) rdev = %d/%d",
                     (S_ISCHR(buf.st_mode)) ? "character" : "block",
                     major(buf.st_rdev), minor(buf.st_rdev));
        }

        printf("\n");
    }

    exit(0);
}
