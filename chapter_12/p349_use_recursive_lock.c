/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : use_recursive_lock.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/10/31
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
#include <time.h>
#include <sys/time.h>

extern int makethread(void *(*)(void *), void *);   //在前一个示例中

typedef struct to_info
{
    void                (*to_fn)(void *);       //function
    void                *to_arg;                //参数
    struct timespec     to_wait;                //time to wait
}to_info;

#define SECTONSEC 1000000000        //seconds to nanoseconds

#if !defined(CLOCK_REALTIME) || defined(BSD)
#define clock_nanosleep(ID, FL, REQ, REM)   nanosleep((REQ), (REM))
#endif

#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME  0
#define USECTIONSEC     1000        //microseconds to nanoseconds

void clock_gettime(int id, struct timespec *tsp)
{
     struct timeval tv;

     gettimeofday(&tv, NULL);
     tsp->tv_sec = tv.tv_sec;
     tsp->tv_nsec = tv.tv_usec * USECTIONSEC;
}

#endif

void * timeout_helper(void *arg)
{
     to_info        *tip = NULL;

     tip = (to_info *)arg;

     clock_nanosleep(CLOCK_REALTIME, 0, &tip->to_wait, NULL);
     (*tip->to_fn)(tip->to_arg);

     free(arg);
     return 0;
}

void timeout(const struct timespec *when, void (*func)(void *), void *arg)
{
     struct timespec    now;
     to_info            *tip = NULL;
     int                err = 0;

     clock_gettime(CLOCK_REALTIME, &now);

     if ((when->tv_sec > now.tv_sec)
             || (when->tv_sec == now.tv_sec && when->tv_nsec > now.tv_nsec))
     {
          tip = (to_info *)malloc(sizeof(to_info));
          if (tip != NULL)
          {
              tip->to_fn = func;
              tip->to_arg = arg;
              tip->to_wait.tv_sec = when->tv_sec - now.tv_sec;
              if (when->tv_nsec >= now.tv_nsec)
              {
                   tip->to_wait.tv_nsec = when->tv_nsec - now.tv_nsec;
              }
              else
              {
                  tip->to_wait.tv_sec--;
                  tip->to_wait.tv_nsec = SECTONSEC - now.tv_nsec + when->tv_nsec;
              }

              err = makethread(timeout_helper, (void *)tip);
              if (err == 0)
              {
                   return ;
              }
              else
              {
                  free(tip);
              }
          }
     }

     //
     (*func)(arg);
}

pthread_mutexattr_t     attr;
pthread_mutex_t         mutex;

void retry(void *arg)
{
     pthread_mutex_lock(&mutex);

     //perform retry steps
     //

     pthread_mutex_unlock(&mutex);
}


int main(void)
{
     int        err = 0;
     int        condition = 0;
     int        arg = 0;
     struct timespec    when;

	 //初始化mutex为recursive（可递归）
     if ((err = pthread_mutexattr_init(&attr)) != 0)
     {
          err_exit(err, "pthread_mutexattr_init failed");
     }
     if ((err = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE)) != 0)
     {
         err_exit(err, "can't set recursive type");
     }
     if ((err = pthread_mutex_init(&mutex, &attr)) != 0)
     {
          err_exit(err, "can't create recursivek mutex");
     }

     pthread_mutex_lock(&mutex);

     if (condition)
     {
          //计算retry的绝对时间
          clock_gettime(CLOCK_REALTIME, &when);
          when.tv_sec += 3;     // 3s
          timeout(&when, retry, (void *)((unsigned long)arg));
     }

     pthread_mutex_unlock(&mutex);

     exit(0);
}
