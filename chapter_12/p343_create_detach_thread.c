/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p343_create_detach_thread.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/10/30
* Description  :
* Function list: 1.
*                2.
*                3.
* History      :
\*=========================================================================*/

/*-----------------------------------------------------------*
 * 头文件                                                    *
 *-----------------------------------------------------------*/
#include <pthread.h>


int
makethread(void *(*fn)(void *), void *arg)
{
    int             err = 0;
    pthread_t       tid;
    pthread_attr_t  attr;

    err = pthread_attr_init(&attr);         //初始化线程属性结构
    if (err != 0)
    {
         return (err);
    }

    //设置分离属性
    err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (err != 0)
    {
        return (err);
    }

    err = pthread_create(&tid, &attr, fn, arg);
    //这里不能出错就返回，因为要先destroy attr
    //

    pthread_attr_destroy(&attr);

    return err;
}
