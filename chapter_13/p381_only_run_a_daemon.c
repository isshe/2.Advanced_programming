/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p381_only_run_a_daemon.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/11/02
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
#include <stdlib.h>
#include <fcntl.h>
#include <syslog.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdio.h>
#include <sys/stat.h>


#define LOCKFILE "/var/run/daemon.pid"
#define LOCKMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

extern int lockfile(int);       //???

int already_running(void)
{
     int        fd = 0;
     char       buf[16] = {0};

     fd = open(LOCKFILE, O_RDWR | O_CREAT, LOCKMODE);
     if (fd < 0)
     {
         syslog(LOG_ERR, "can't open %s: %s", LOCKFILE, strerror(errno));
         exit(1);
     }

     if (lockfile(fd) < 0)
     {
          //??????
          if (errno == EACCES || errno == EAGAIN)
          {
              syslog(LOG_ERR, "daemon is already_running");
              close(fd);
              return 1;
          }

          syslog(LOG_ERR, "can't lock %s: %s", LOCKFILE, strerror(errno));
          exit(1);
     }

     ftruncate(fd, 0);      //???P90
     sprintf(buf, "%ld", (long)getpid());
     write(fd, buf, strlen(buf) + 1);
     syslog(LOG_ERR, "write /var/run/daemon.pid: %s", buf);

     return 0;
}
