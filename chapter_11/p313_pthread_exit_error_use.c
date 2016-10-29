/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p313_pthread_exit_error_use.c
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

typedef struct FOO_S_
{
    int a;
    int b;
    int c;
    int d;
}foo;

void
printfoo(const char *s, const foo *fp)
{
     printf("%s", s);
     printf(" structure at 0x%lx\n", (unsigned long)fp);
     printf(" foo.a = %d\n", fp->a);
     printf(" foo.b = %d\n", fp->b);
     printf(" foo.c = %d\n", fp->c);
     printf(" foo.d = %d\n", fp->d);
}

void *
thr_fn1(void *arg)
{
     foo foo = {1,2,3,4};

     printfoo("thread 1:\n", &foo);
     pthread_exit((void*)&foo);
}

void *
thr_fn2(void *arg)
{
     printf("thread 2: ID is %lu\n", (unsigned long)pthread_self());
     pthread_exit((void*)0);
}

int
main(void)
{
     int        err = 0;
     pthread_t  tid1, tid2;
     foo        *fp = NULL;

     err = pthread_create(&tid1, NULL, thr_fn1, NULL);
     if (err != 0)
     {
          err_exit(err, "can't create thread 1");
     }
     err = pthread_join(tid1, (void*)&fp);
     if (err != 0)
     {
         err_exit(err, "can't join with thread 1");
     }
     sleep(1);

     printf("parent staring second thread\n");

     err = pthread_create(&tid2, NULL, thr_fn2, NULL);
     if (err != 0)
     {
          err_exit(err, "can't create thread 2");
     }
     err = pthread_join(tid2, (void*)&fp);
     if (err != 0)
     {
         err_exit(err, "can't join with thread 2");
     }
     sleep(1);

    printfoo("parent:\n", fp);
    exit(0);
}
