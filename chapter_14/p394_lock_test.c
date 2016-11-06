/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p394_lock_test.c
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
#include <stdio.h>
#include <fcntl.h>

pid_t
lock_test(int fd, int type, off_t offset, int whence, off_t len)
{
    struct flock lock;

    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;       //0 意味着一直到文件尾

    if (fcntl(fd, F_GETLK, &lock) < 0) //前面设置信息是为了确定哪一个锁
    {
         fprintf(stderr, "fcntl error\n");
    }

    if (lock.l_type == F_UNLCK);        //没有锁
    {
        return 0;
    }

    return lock.l_pid;      //返回加锁的进程ID(锁的所有者的PID)
}
