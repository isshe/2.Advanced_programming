/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p310_print_thread_ID.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/10/28
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

pthread_t   ntid;

void printids(const char *s)
{
     pid_t          pid;
     pthread_t      tid;

     pid = getpid();
     tid = pthread_self();

     printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long)pid,
             (unsigned long)tid, (unsigned long)tid);
}

void *
thr_fn(void *arg)
{
     printids("new thread: ");
     return ((void *)0);
}

int
main(void)
{
     int err;

     err = pthread_create(&ntid, NULL, thr_fn, NULL);
     if (err != 0)
     {
          err_exit(err, "can't create thread");
     }

     printids("mian thread: ");
     sleep(1);
     exit(0);
}
