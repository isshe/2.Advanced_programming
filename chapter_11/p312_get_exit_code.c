/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p312_get_exit_code.c
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

void *
thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    sleep(1);
    return ((void*)1);
}

void *
thr_fn2(void *arg)
{
     printf("thread 2 exiting\n");
     pthread_exit((void*)2);
}

int
main(void)
{
     int        err = 0;
     pthread_t  tid1, tid2;
     void       *tret = NULL;

     err = pthread_create(&tid1, NULL, thr_fn1, NULL);
     if (err != 0)
     {
          err_exit(err, "can't create thread 1");
     }

     err = pthread_create(&tid2, NULL, thr_fn2, NULL);
     if (err != 0)
     {
         err_exit(err, "can't create thread 2");
     }

     //等待thread 1 退出，以及获取它的返回值
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
     printf("threadf 2 exit code %ld\n", (long)tret);

     exit(0);
}
