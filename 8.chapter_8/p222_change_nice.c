/*==============================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p222_change_nice.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/01/03
* Description  : 更改nice值的效果
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"
#include <errno.h>
#include <sys/time.h>

#if defined(MACOS)
#include <sys/syslimits.h>
#elif defined(SOLARIS)
#include <limits.h>
#elif defined (BSD)
#include <sys/param.h>
#endif

unsigned long long count;
struct  timeval     end;

void checktime(char *str)
{
     struct timeval     tv;

     gettimeofday(&tv, NULL);       //
     if (tv.tv_sec > end.tv_sec &&tv.tv_usec >= end.tv_usec)
     {
          printf("%s count = %lld\n", str, count);

          exit(0);
     }
}

int
main(int argc, char *argv[])
{
     pid_t  pid;
     char   *s;
     int    nzero = 0;
     int    ret = 0;
     int    adj = 0;

     setbuf(stdout, NULL);      //unbuffered

#if defined(NZERO)
     nzere = NZERO;
#elif defined(_SC_NZERO)
     nzero = sysconf(_SC_NZERO);
#else
#error NZERO undefined
#endif

     printf("NZERO = %d\n", nzero);
     if (argc == 2)
     {
          adj = strtol(argv[1], NULL, 10);      //strtol???
     }
     gettimeofday(&end, NULL);
     end.tv_sec += 10;

     if ((pid = fork()) < 0)
     {
          err_sys("fork error");
     }
     else if (pid == 0)
     {
          s = "child";
          printf("current nice value in child is %d, adjusting by %d\n",
                  nice(0)+nzero, adj);
          errno = 0;

          if ((ret = nice(adj)) == -1 && errno != 0)
          {
               err_sys("nice error");
          }

          printf("now child nice value is %d\n", ret+nzero);
     }
     else
     {
          s = "parent";
          printf("current nice value in parent is %d\n", nice(0) + nzero);
     }

     for (;;)
     {
          if (++count == 0)
          {
              err_quit("%s counter wrap", s);
          }
          checktime(s);
     }
}
