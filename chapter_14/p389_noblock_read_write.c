/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p389_noblock_read_write.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/11/05
* Description  :
* Function list: 1.
*                2.
*                3.
* History      :
\*=========================================================================*/

/*-----------------------------------------------------------*
 * 头文件                                                    *
 *-----------------------------------------------------------*/
#include "apue.h"
#include <errno.h>
#include <fcntl.h>

char    buf[5000000];
extern void clr_fl(int fd, int flags);
extern void set_fl(int fd, int flags);


int main(void)
{
     int        ntowrite = 0;
     int        nwrite = 0;
     char       *ptr = NULL;

     ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
     fprintf(stderr, "reawd %d bytes\n", ntowrite);

     set_fl(STDOUT_FILENO, O_NONBLOCK);     //设置为非阻塞

     ptr = buf;

     while(ntowrite > 0)
     {
          errno = 0;
          nwrite = write(STDOUT_FILENO, ptr, ntowrite);
          fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);

          if (nwrite > 0)
          {
              ptr += nwrite;
              ntowrite -= nwrite;
          }
     }

     clr_fl(STDOUT_FILENO, O_NONBLOCK);     //清除

     exit(0);
}
