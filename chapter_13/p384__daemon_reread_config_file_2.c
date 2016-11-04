/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p384__daemon_reread_config_file_2.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/11/04
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
#include <syslog.h>
#include <errno.h>

extern int lockfile(int);
extern int already_running(void);
extern void daemonize(const char *cmd);

void reread(void)
{
     //
}

void sigterm(int signo)
{
    syslog(LOG_INFO, "got SIGTERM; exiting");
    exit(0);
}

void sighup(int signo)
{
     syslog(LOG_INFO, "Re-reading confituration file");
     reread();  ///
}

int main(int argc, char *argv[])
{
    char                *cmd = NULL;
    struct sigaction    sa;

    if ((cmd = strrchr(argv[0], '/')) == NULL)
    {
         cmd = argv[0];
    }
    else
    {
        cmd++;  //指向程序名
    }

    daemonize(cmd);

    //确定只有一个守护进程在运行
    if (already_running())
    {
         syslog(LOG_ERR, "daemon already_running");
         exit(1);
    }

    //handle signals of interest.
    sa.sa_handler = sigterm;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGHUP);         //把SIGHUP加到屏蔽信号集中
    sa.sa_flags = 0;
    if (sigaction(SIGTERM, &sa, NULL) < 0)
    {
         syslog(LOG_ERR, "can't catch SIGTERM: %s", strerror(errno));
         exit(1);
    }

     sa.sa_handler = sighup;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGTERM);         //把SIGHUP加到屏蔽信号集中
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0)
    {
         syslog(LOG_ERR, "can't catch SIGHUP: %s", strerror(errno));
         exit(1);
    }

    //自定义kill
    kill(getpid(), SIGHUP);
    sleep(1);

    exit(0);
}
