/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p102_futimens.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/11/24
* Description  : 使用带O_TRUNC选项的open函数将文件截断为0,
*                   并不更改其访问时间及修改时间.
*               首先用stat函数得到这些时间;
*               然后截断文件;
*               最后用futimens函数重置这两个时间.
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"
#include <fcntl.h>

int
main(int argc, char *argv[])
{
     int    i = 0;
     int    fd = 0;
     struct stat    statbuf;
     struct timespec    times[2];

     for (i = 1; i < argc; i++)
     {
          if (stat(argv[i], &statbuf) < 0)
          {
              err_ret("%s: stat error", argv[i]);
              continue;
          }

          if ((fd = open(argv[1], O_RDWR | O_TRUNC)) < 0)
          {
               err_ret("%s: open error", argv[i]);
               continue;
          }

          times[0] = statbuf.st_atim;
          times[1] = statbuf.st_mtim;
          if (futimens(fd, times) < 0)
          {
               err_ret("%s: futimens error", argv[i]);
          }

          close(fd);
     }

     exit(0);
}
