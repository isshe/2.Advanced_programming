/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p328_pthread_mutex_timelock.c
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
#include <apue.h>
#include <pthread.h>

int main(void)
{
    int                 err = 0;
    struct timespec     tout;
    struct tm           *tmp = NULL;
    char                buf[64] = {0};
    pthread_mutex_t     lock = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&lock);
    printf("mutex is locked\n");
    clock_gettime(CLOCK_REALTIME, &tout);
    tmp = localtime(&tout.tv_sec);
    strftime(buf, sizeof(buf), "%r", tmp);  //把时间转换为str格式
    printf("current time is %s\n", buf);

    tout.tv_sec += 3;      //10s

    err = pthread_mutex_timedlock(&lock, &tout);
    clock_gettime(CLOCK_REALTIME, &tout);
    tmp = localtime(&tout.tv_sec);
    strftime(buf, sizeof(buf), "%r", tmp);
    printf("the time is now %s\n", buf);

    if (err == 0)
    {
         printf("mutex locked again\n");
    }
    else
    {
        printf("can't lock mutex again: %s\n", strerror(errno));
    }

    exit(0);
}
