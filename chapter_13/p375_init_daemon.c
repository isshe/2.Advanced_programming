/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p375_init_daemon.c
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
#include "apue.h"
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>

void daemonize(const char *cmd)
{
    int                 i = 0;
    int                 fd0 = 0;
    int                 fd1 = 0;
    int                 fd2 = 0;
    pid_t               pid;
    struct rlimit       rl;
    struct sigaction    sa;

    //清除“文件模式创建屏蔽字”
    umask(0);

    //获取最大文件描述符
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
    {
         err_quit("%s: can't get file limit", cmd);
    }

    //创建一个新会话
    if ((pid = fork()) < 0)
    {
        err_quit("%s: can't fork", cmd);
    }
    else if (pid != 0)  //父进程
    {
         exit(0);
    }
    setsid();       //

    //确保以后不会分配控制终端
    sa.sa_handler = SIG_IGN;    //
    sigemptyset(&sa.sa_mask);   //
    if (sigaction(SIGHUP, &sa, NULL) < 0)
    {
         err_quit("%s: can't ignore SIGHUP", cmd);
    }

    if ((pid = fork()) < 0)
    {
        err_quit("%s:can't fork", cmd);
    }
    else if (pid != 0)
    {
         exit(0);
    }

    //改变当前工作目录为根目录
    if (chdir("/") < 0)
    {
        err_quit("%s: can't change directory to /", cmd);
    }

    //关闭所有打开的文件描述符
    if (rl.rlim_max == RLIM_INFINITY)
    {
         rl.rlim_max = 1024;
    }

    for (i = 0; i < rl.rlim_max; i++)
    {
        close(i);       //关闭文件描述符
    }

    //定向文件描述符0，1，2到/dev/null
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

    //初始化log file
    openlog(cmd, LOG_CONS, LOG_DAEMON);         //???
    if (fd0 != 0 || fd1 != 1 || fd2 != 2)
    {
         syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
         exit(1);
    }
}
