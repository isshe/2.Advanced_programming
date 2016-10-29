/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p322_use_mutex.c
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

typedef struct foo
{
    int             f_count;
    pthread_mutex_t f_lock;
    int             f_id;
    //more stuff here...
}foo;

foo *foo_alloc(int id)
{
     foo    *fp = NULL;

     if ((fp = (foo *)malloc(sizeof(foo))) != NULL)
     {
         fp->f_count = 1;
         fp->f_id = id;
         if (pthread_mutex_init(&fp->f_lock, NULL) != 0)
         {
              free(fp);
              return NULL;
         }
         //continue initialization ...
     }

     return fp;
}

void foo_hold(foo *fp)
{
     pthread_mutex_lock(&fp->f_lock);
     fp->f_count++;
     pthread_mutex_unlock(&fp->f_lock);
}

void foo_rele(foo *fp)
{
     pthread_mutex_lock(&fp->f_lock);

     fp->f_count--;

     if (fp->f_count == 0)
     {
         pthread_mutex_unlock(&fp->f_lock);
         pthread_mutex_destroy(&fp->f_lock);
         free(fp);
     }
     else
     {
          pthread_mutex_unlock(&fp->f_lock);
     }
}
