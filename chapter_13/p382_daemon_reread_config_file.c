/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p382_daemon_reread_config_file.c
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
#include <pthread.h>
#include <syslog.h>

sigset_t    mask;

extern int already_running(void);
extern void daemonize(const char *cmd);


void reread(void)
{
     //
}

void * thr_fn(void *arg)
{
    int         err = 0;
    int         signo = 0;

    while(1)
    {
         syslog(LOG_INFO, "thr_fn while(1) before sigwait");
         err = sigwait(&mask, &signo);  //mask需要设置
         if (err != 0)
         {
             syslog(LOG_ERR, "sigwait failed");
             exit (1);
         }

         switch(signo)
         {
             case SIGHUP:
                 syslog(LOG_INFO, "Re-reading configuration file");
                 reread();
                 break;

             case SIGTERM:
                 syslog(LOG_INFO, "got SIGTERM; exiting");
                 exit(0);

             default:
                 syslog(LOG_INFO, "unexpected signal %d\n", signo);
         }
    }

    return 0;
}

int main(int argc, char *argv[])
{
     int                err = 0;
     pthread_t          tid ;
     char               *cmd = NULL;
     struct sigaction   sa;

     if ((cmd = strrchr(argv[0], '/')) == NULL)
     {
          cmd = argv[0];
     }
     else
     {
         cmd++;
     }

     syslog(LOG_ERR, "before daemonize !!!!!!!!!!!!!!!!!!");
     //变为守护进程
     daemonize(cmd);


     //确保只有一个守护进程副本在运行
     if (already_running())
     {
          syslog(LOG_ERR, "daemon alread running");
          exit(1);
     }

     //restore SIGHUP default and block all signal
     sa.sa_handler = SIG_DFL;       //???
     sigemptyset(&sa.sa_mask);
     sa.sa_flags = 0;               //???

     if (sigaction(SIGHUP, &sa, NULL) < 0)
     {
          err_quit("%s: can't restore SIGHUP default");
     }

     sigfillset(&mask);     // 把所有信号都放到mask集合里面

     //把mask信号集里的信号添加到线程的信号屏蔽集里面
     if ((err = pthread_sigmask(SIG_BLOCK, &mask, NULL)) != 0)
     {
          err_exit(err, "SIG_BLOCK error");
     }

     //新建一个线程处理SIGHUP 和SIGTERM
     syslog(LOG_ERR, "before pthread_create");
     err = pthread_create(&tid, NULL, thr_fn, 0);
     if (err != 0)
     {
          err_exit(err, "can't create thread");
     }

     //kill 自定义
     kill(getpid(), SIGHUP);
     sleep(1);
     //proceed with the rest of the daemon
     //

     exit(0);
}
