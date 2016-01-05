/*==============================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p263_getpwnam_signal.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/01/05
* Description  : 这段程序从信号处理程序my_alarm调用非可重入函数getpwanm， 而
*                   my_alarm每秒钟调用一次。实验表明，my_alarm中的getpwnam会
*                   影响到信号。原因暂时不懂， 日后看此书第二遍。
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"
#include <pwd.h>

static void
my_alarm(int signo)
{
    struct  passwd  *rootptr;

    printf("in signal handler\n");
    if ((rootptr = getpwnam("isshe")) == NULL)
    {
         err_sys("getpwnam(root) error");
    }

 //   printf(" rootptr->pw_name = %s\n", rootptr->pw_name);
   alarm(1);
}

int main(void)
{
     struct     passwd  *ptr;

     signal(SIGALRM, my_alarm);
     alarm(1);

     for ( ; ; )
     {
//          alarm(1);
          if ((ptr = getpwnam("isshe")) == NULL)
          {
              err_sys("getpwnam(isshe) error");
          }

          if (strcmp(ptr->pw_name, "isshe") != 0)
          {
               printf("return value corrupted, pw_name = %s\n", ptr->pw_name);
          }
     }
}
