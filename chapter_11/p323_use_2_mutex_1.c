/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p323_use_2_mutex_1.c
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
#include <stdlib.h>
#include <pthread.h>

#define NHASH           29
#define HASH(id)        (((unsigned long)id)%NHASH)

pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;

typedef struct foo
{
     int                f_count;
     pthread_mutex_t    f_lock;
     int                f_id;
     struct foo         *f_next;
}foo;

foo *fh[NHASH];

foo *foo_alloc(int id)
{
     foo    *fp = NULL;
     int    idx = 0;

     if ((fp = (foo *)malloc(sizeof(foo))) != NULL)
     {
         fp->f_count = 1;
         fp->f_id = id;

         if (pthread_mutex_init(&fp->f_lock, NULL) != 0)
         {
              free(fp);
              return (NULL);
         }

         idx = HASH(id);

         //第一个锁
         pthread_mutex_lock(&hashlock);
         fp->f_next = fh[idx];
         fh[idx] = fp;

         //第二个锁
         pthread_mutex_lock(&fp->f_lock);
         pthread_mutex_unlock(&hashlock);

         pthread_mutex_unlock(&fp->f_lock);
     }
     return (fp);
}


void foo_hold(foo *fp)
{
    pthread_mutex_lock(&fp->f_lock);
    fp->f_count++;
    pthread_mutex_unlock(&fp->f_lock);
}

foo * foo_find(int id)
{
     foo *fp = NULL;

     pthread_mutex_lock(&hashlock);

     for(fp = fh[HASH(id)]; fp != NULL; fp = fp->f_next)
     {
         if (fp->f_id == id)
         {
              foo_hold(fp);
              break;
         }
     }

     pthread_mutex_unlock(&hashlock);

     return (fp);
}

void foo_rele(foo *fp)
{
     foo    *tfp = NULL;
     int    idx = 0;

     pthread_mutex_lock(&fp->f_lock);

     if (fp->f_count == 1)
     {
          pthread_mutex_unlock(&fp->f_lock);
          pthread_mutex_lock(&hashlock);
          pthread_mutex_lock(&fp->f_lock);

          //需要重新检查，为何？？？
          if (fp->f_count != 1)
          {
               fp->f_count--;
               pthread_mutex_unlock(&fp->f_lock);
               pthread_mutex_unlock(&hashlock);
               return;
          }

          //remove from list
          idx = HASH(fp->f_id);
          tfp = fh[idx];
          if (tfp == fp)
          {
               fh[idx] = fp->f_next;
          }
          else
          {
              while(tfp->f_next != fp)
              {
                  tfp = tfp->f_next;
              }
              tfp->f_next = fp->f_next;
          }
          pthread_mutex_unlock(&hashlock);
          pthread_mutex_unlock(&fp->f_lock);
          pthread_mutex_destroy(&fp->f_lock);
          free(fp);
     }
     else
     {
          fp->f_count--;
          pthread_mutex_unlock(&fp->f_lock);
     }
}
