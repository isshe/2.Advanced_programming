/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p334_use_cond.c
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

typedef struct msg
{
    struct msg  *m_next;
}msg;


msg *workq;
pthread_cond_t  qready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

void process_msg(void)
{
     msg *mp = NULL;

     while(1)
     {
         pthread_mutex_lock(&qlock);

         while(workq == NULL)
         {
              pthread_cond_wait(&qready, &qlock);
         }

         mp = workq;
         workq = mp->m_next;

         pthread_mutex_unlock(&qlock);
     }
}

void enqueue_msg(msg *mp)
{
     pthread_mutex_lock(&qlock);

     mp->m_next = workq;
     workq = mp;

     pthread_mutex_unlock(&qlock);

     pthread_cond_signal(&qready);
}
