/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p94_unlink.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/11/23
* Description  : 打开一个文件, 然后解除它的链接.
*                   执行该程序的进程然后睡眠15秒, 接着终止.
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"
#include <fcntl.h>

int
main(void)
{
     if (open("test_link", O_RDWR) < 0)
     {
         err_sys("open error");
     }
     if (unlink("test_link") < 0)
     {
          err_sys("unlink error");
     }

     printf("file unlinked\n");
     sleep(15);
     printf("done\n");

     exit(0);
}
