/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p316_thread_cleanup_func.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/10/29
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

void cleanup(void *arg)
{
    printf("cleanup: %s\n", (char *)arg);
}

void *
thr_fn1(void *arg)
{
     printf("thread 1 start\n");
     pthread_cleanup_push(cleanup, "thread 1 first handler");
     pthread_cleanup_push(cleanup, "thread 1 second handler");
     printf("thread 1 push complete\n");

     if (arg)
     {
          return ((void *)1);
     }

     pthread_cleanup_pop(0);
     pthread_cleanup_pop(0);
     return ((void *)1);
}


void *
thr_fn2(void *arg)
{
     printf("thread 2 start\n");
     pthread_cleanup_push(cleanup, "thread 2 first handler");
     pthread_cleanup_push(cleanup, "thread 2 second handler");
     printf("thread 2 push complete\n");

     if (arg)
     {
          pthread_exit ((void *)2);
     }

     pthread_cleanup_pop(0);
     pthread_cleanup_pop(0);
     pthread_exit((void *)2);
}

int
main(void)
{
     int        err = 0;
     pthread_t  tid1, tid2;
     void       *tret = NULL;
     int        arg = 1;

     err = pthread_create(&tid1, NULL, thr_fn1, NULL);//(void *)&arg);
     if (err != 0)
     {
          err_exit(err, "can't create thread 1");
     }

     err = pthread_create(&tid2, NULL, thr_fn2, (void *)&arg);
     if (err != 0)
     {
          err_exit(err, "can't create thread 2");
     }

     err = pthread_join(tid1, &tret);
     if (err != 0)
     {
          err_exit(err, "can't join with thread 1");
     }
     printf("thread 1 exit code %ld\n", (long)tret);

     err = pthread_join(tid2, &tret);
     if (err != 0)
     {
          err_exit(err, "can't join with thread 2");
     }
     printf("thread 2 exit code %ld\n", (long)tret);

     exit(0);
}
