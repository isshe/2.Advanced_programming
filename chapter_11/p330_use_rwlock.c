/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p330_use_rwlock.c
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
#include <stdlib.h>
#include <pthread.h>

typedef struct job
{
     struct job *j_next;
     struct job *j_prev;
     pthread_t  j_id;       //tells which thread handlers this job

}job;

typedef struct queue
{
     struct job         *q_head;
     struct job         *q_tail;
     pthread_rwlock_t   q_lock;
}queue;

//初始化队列
int queue_init(queue *qp)
{
     int    err = 0;

     qp->q_head = NULL;
     qp->q_tail = NULL;

     err = pthread_rwlock_init(&qp->q_lock, NULL);
     if (err != 0)
     {
          return (err);
     }

     return 0;
}

//在队列头部插入一个job
void job_insert(queue *qp, job *jp)
{
     pthread_rwlock_wrlock(&qp->q_lock);        //写锁
     jp->j_next = qp->q_head;
     jp->j_prev = NULL;
     if (qp->q_head != NULL)
     {
          qp->q_head->j_prev = jp;
     }
     else
     {
          qp->q_tail = jp;  //空链表
     }

     qp->q_head = jp;

     pthread_rwlock_unlock(&qp->q_lock);
}

//在队尾追加一个job
void job_append(queue *qp, job *jp)
{
     pthread_rwlock_wrlock(&qp->q_lock);
     jp->j_next = NULL;
     jp->j_prev = qp->q_tail;

     if (qp->q_tail != NULL)    //非空
     {
          qp->q_tail->j_next = jp;
     }
     else
     {
          qp->q_head = jp;
     }

     qp->q_tail = jp;

     pthread_rwlock_unlock(&qp->q_lock);
}

//删除指定queue中指定的job
void jobi_remove(queue *qp, job *jp)
{
     pthread_rwlock_wrlock(&qp->q_lock);

     if (jp == qp->q_head)
     {
          qp->q_head = jp->j_next;
          if (qp->q_tail == jp)
          {
              qp->q_tail = NULL;    //空了
          }
          else
          {
               jp->j_next->j_prev = jp->j_prev;
          }
     }
     else if (jp == qp->q_tail)     //尾节点
     {
          qp->q_tail = jp->j_prev;
          jp->j_prev->j_next = jp->j_next;
     }
     else
     {
          jp->j_prev->j_next = jp->j_next;
          jp->j_next->j_prev = jp->j_prev;
     }

     pthread_rwlock_unlock(&qp->q_lock);
}

//通过thread id 找job
job *job_find(queue *qp, pthread_t id)
{
     job *jp = NULL;

     if (pthread_rwlock_rdlock(&qp->q_lock) != 0)
     {
          return NULL;
     }

     for (jp = qp->q_head; jp != NULL; jp = jp->j_next)
     {
          if (pthread_equal(jp->j_id, id) != 0)     //相等
          {
              break;
          }
     }

     pthread_rwlock_unlock(&qp->q_lock);

     return jp;
}
