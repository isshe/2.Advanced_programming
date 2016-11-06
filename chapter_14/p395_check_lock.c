/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p396_check_lock.c
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
#include <fcntl.h>

extern int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len);

#define writew_lock(fd, offset, whence, len) \
    lock_reg((fd), F_SETLKW, F_WRLCK, (offset), (whence), (len))


static void lockabyte(const char *name, int fd, off_t offset)
{
    if (writew_lock(fd, offset, SEEK_SET, 1) < 0)
    {
        err_sys("%s: writew_lock error", name);
    }
    printf("%s: got the lock, byte %lld\n", name, (long long)offset);
}


int
main(void)
{
     int        fd = 0;
     pid_t      pid ;

     //create file and write 2 bytes to it
     if ((fd = creat("templock", FILE_MODE)) < 0)
     {
         err_sys("creat error");
     }

     if (write(fd, "ab", 2) != 2)
     {
          err_sys("write error");
     }

     TELL_WAIT();       // 8.9节

     if ((pid = fork()) < 0)
     {
          err_sys("fork error");
     }
     else if (pid == 0)     //child
     {
         //锁第一个字节，请求其二个字节
         lockabyte("child", fd, 0);
         TELL_PARENT(getppid());
         WAIT_PARENT();
         lockabyte("child", fd, 1);
     }
     else
     {
          //锁第二个字节，请求第一个字节
          lockabyte("parent", fd, 1);
          TELL_CHILD(pid);
          WAIT_CHILD();
          lockabyte("parent", fd, 0);
     }

     exit(0);
}
