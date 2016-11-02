/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p366_deal_with_syn_signal.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/11/01
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

int         quitflag;       //set nonzero by thread
sigset_t    mask;

pthread_mutex_t     lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t      waitloc = PTHREAD_COND_INITIALIZER;

void *
thr_fn(void *arg)
{
     int        err = 0;
     int        signo = 0;

     while(1)
     {
         err = sigwait(&mask, &signo);      //等信号集中的信号。
         if (err != 0)
         {
              err_exit(err, "sigwait failed");
         }

         printf("signo = %d\n", signo);
         switch(signo)
         {
             case SIGINT:
                 printf("\ninterrupt\n");
                 break;

             case SIGQUIT:
                 pthread_mutex_lock(&lock);
                 quitflag = 1;
                 pthread_mutex_unlock(&lock);
                 pthread_cond_signal(&waitloc);
                 return 0;

             default:
                 printf("unexpected signal %d\n", signo);
                 exit(1);
         }
     }
}

int main(void)
{
     int        err = 0;
     sigset_t   oldmask;
     pthread_t  tid;

     sigemptyset(&mask);
     sigaddset(&mask, SIGINT);
     sigaddset(&mask, SIGQUIT);

     if ((err = pthread_sigmask(SIG_BLOCK, &mask, &oldmask)) != 0)
     {
          err_exit(err, "pthread_sigmask SIG_BLOCK error");
     }

     err = pthread_create(&tid, NULL, thr_fn, 0);
     if (err != 0)
     {
         err_exit(err, "can't create thread");
     }

     pthread_mutex_lock(&lock);

     while(quitflag == 0)
     {
          pthread_cond_wait(&waitloc, &lock);
     }

     pthread_mutex_unlock(&lock);

     quitflag = 0;

     //恢复oldmask
     if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
     {
          err_sys("SIG_SETMASK error");
     }

     exit(0);
}
