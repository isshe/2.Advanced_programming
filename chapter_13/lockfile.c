/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : lockfile.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/11/03
* Description  :
* Function list: 1.
*                2.
*                3.
* History      :
\*=========================================================================*/

/*-----------------------------------------------------------*
 * 头文件                                                    *
 *-----------------------------------------------------------*/
#include <unistd.h>
#include <fcntl.h>

int lockfile(int fd)
{
    struct flock fl;

    fl.l_type = F_WRLCK;
    fl.l_start = 0;
    fl.l_whence = SEEK_SET;
    fl.l_len = 0;

    return (fcntl(fd, F_SETLK, &fl));
}
