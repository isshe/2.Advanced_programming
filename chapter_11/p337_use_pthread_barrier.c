/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p337_use_pthread_barrier.c
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
#include "apue.h"
#include <pthread.h>
#include <limits.h>
#include <sys/time.h>

#define NTHR        8               //number of threads
#define NUMNUM      8000000L        //需要排序的数据个数
#define TNUM        (NUMNUM/NTHR)   //每个线程排序多少数据

long nums[NUMNUM];
long snums[NUMNUM];

pthread_barrier_t   b;

#define heapsort qsort
/*
#ifdef SOLARIS
#define heapsort qsort
#else
extern int heapsort(void *, size_t, size_t ,
        int (*)(const void *, const void *));
#endif
*/


//比较两个长整型
int complong(const void *arg1, const void *arg2)
{
     long l1 = *(long *)arg1;
     long l2 = *(long *)arg2;

     if (l1 == l2)
     {
         return 0;
     }
     else if (l1 < l2)
     {
          return -1;
     }
     else
     {
         return 1;
     }
}


//排序线程
void *thr_fn(void *arg)
{
     long   idx = (long)arg;

     heapsort(&nums[idx], TNUM, sizeof(long), complong);
     pthread_barrier_wait(&b);      //等待所有线程都排序完

     return ((void *)0);
}

//合并
void merge()
{
     long idx[NTHR];
     long i = 0;
     long minidx = 0;
     long sidx = 0;
     long num = 0;

     //每个线程的开始的index
     for (i = 0; i < NTHR; i++)
     {
          idx[i] = i * TNUM;
     }

     //循环NUMNUM次，每次从NTHR个线程排序的数组中取一个最小的数，
     //放到目标数组snums中。
     //时间复杂度是(NTHR*NUMNUM)
     //空间复杂度是(2*NUMNUM)
     for (sidx = 0; sidx < NUMNUM; sidx++)
     {
          num = LONG_MAX;    //???

          for (i = 0; i < NTHR; i++)
          {
               if ((idx[i] < (i + 1) * TNUM)
                       && (nums[idx[i]] < num))
               {
                   num = nums[idx[i]];
                   minidx = i;
               }
          }
          snums[sidx] = nums[idx[minidx]];
          idx[minidx]++;
     }
}


int main(void)
{
     unsigned long      i = 0;
     struct timeval     start, end;
     long long          startusec, endusec;
     double             elapsed = 0.0;
     int                err = 0;
     pthread_t          tid[NTHR];

     //新建数组
     srandom(1);        //???
     for (i = 0; i < NUMNUM; i++)
     {
          nums[i] = random();
//          printf("%ld\n", nums[i]);
     }

     //新建NTHR个线程
     gettimeofday(&start, NULL);
     pthread_barrier_init(&b, NULL, NTHR + 1);      //这里为什么要NTHR + 1

     for (i = 0; i < NTHR; i++)
     {
          err = pthread_create(&tid[i], NULL, thr_fn, (void *)(i * TNUM));
          if (err != 0)
          {
               err_exit(err, "can't create thread");
          }
     }

     pthread_barrier_wait(&b);
     //合并
     merge();

     gettimeofday(&end, NULL);

     //打印
     startusec = start.tv_sec * 1000000 + start.tv_usec;
     endusec = end.tv_sec * 1000000 + end.tv_usec;
     elapsed = (double)(endusec - startusec) / 1000000.0;

     printf("sort took %.4f seconds\n", elapsed);

     for (i = 0; i < NUMNUM; i++)
     {
          printf("%ld\n", snums[i]);
/*
          if (i % 8 == 0)
          {
              printf("\n");
          }
*/
     }
     
     printf("\nsort took %.4f seconds\n\n", elapsed);
     
     exit(0);
}
