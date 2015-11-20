/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p86_chmod.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/11/20
* Description  : 设置文件权限
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"

int main(void)
{
     struct stat    statbuf;

     /*turn on set-group-ID and turn off group-execute */
     if (stat("foo", &statbuf) < 0)
     {
          err_sys("stat error for foo");
     }
     if (chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
     {
          err_sys("chmod error for foo");
     }

     //set absolute mode to "rw-r--r--"
     if (chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
     {
          err_sys("chmod error for bar");
     }

     exit(0);
}
