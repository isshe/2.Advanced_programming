/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p55_file_oprate.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/11/09
* Description  :
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void)
{
     int fd = 0;

     if ((fd = creat("file.hole", FILE_MODE)) < 0)  //FIEL_MODE在apue.h定义
     {
          err_sys("creat error");
     }

     if (write(fd, buf1, 10) != 10)
     {
          err_sys("buf1 write error");
     }
     //offset now = 10

     if (lseek(fd, 16384, SEEK_SET) == -1)
     {
          err_sys("lseek error");
     }
     //offset now = 16384

     if (write(fd, buf2, 10) != 10)
     {
          err_sys("buf2 write error");
     }
     //offset now = 16394
     //

     exit(0);
}
