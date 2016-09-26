/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p295_system.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/09/26
* Description  :
* Function list: 1.
*                2.
*                3.
* History      :
\*=========================================================================*/

/*-----------------------------------------------------------*
 * 头文件                                                    *
 *-----------------------------------------------------------*/
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

int system(const char *cmdstring)
{
     pid_t              pid;
     int                status;
     struct sigaction   ignore;
     struct sigaction   saveintr;
     struct sigaction   savequit;
     sigset_t           chldmask;
     sigset_t           savemask;

     if (cmdstring == NULL)
        return (1);

     ignore.sa_handler = SIG_IGN;   //ignore SIGINT and SIGQUIT
     sigemptyset(&ignore.sa_mask);  //
     ignore.sa_flags = 0;
     if (sigaction(SIGINT, &ignore, &saveintr) < 0)         //原来的环境保存到了saveintr
     {
          return (-1);
     }
     if (sigaction(SIGQUIT, &ignore, &savequit) < 0)
     {
         return (-1);
     }

     //阻塞SIGCHLD
     sigemptyset(&chldmask);
     sigaddset(&chldmask, SIGCHLD);
     if (sigprocmask(SIG_BLOCK, &chldmask, &savemask) < 0)  //原来的屏蔽集保存到了savemask
     {
          return -1;
     }

     if ((pid = fork()) < 0)
     {
          status = -1;
     }
     else if (0 == pid)     //子进程处理相关命令
     {
         //还原信号处理以及还原信号集
         sigaction(SIGINT, &saveintr, NULL);
         sigaction(SIGQUIT, &savequit, NULL);       //注意一个stuct sigaction变量只对应一个信号
         sigprocmask(SIG_SETMASK, &savemask, NULL);

         execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
         _exit(127);  //exec error
     }
     else   //父进程等待子进程结束
     {
          while(waitpid(pid, &status, 0) < 0)
          {
              if (errno != EINTR)
              {
                  status = -1;
                  break;
              }
          }
     }

     //父进程还原信号处理以及还原屏蔽信号集
     if (sigaction(SIGINT, &saveintr, NULL) < 0)
         return -1;
     if (sigaction(SIGQUIT, &savequit, NULL) < 0)
         return -1;
     if (sigprocmask(SIG_SETMASK, &savemask, NULL) < 0)
         return -1;

     return (status);
}
