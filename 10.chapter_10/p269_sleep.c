/*==============================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p269_sleep.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/01/06
* Description  : sleep的简化而不完整的实现
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include <signal.h>
#include <unistd.h>
#include <stdio.h>


static void
sig_alrm(int signo)
{
    ;//nothing to do
}

unsigned int
sleep1(unsigned int seconds)
{
     if (signal(SIGALRM, sig_alrm) == SIG_ERR)
     {
         return(seconds);
     }

     alarm(seconds);
     pause();
     return(alarm(0));          //turn off timer, return unslept time
}

int
main(void)
{
    unsigned int sle_ret;

     printf("before sleep1\n");
     sle_ret = sleep1(1);
     printf("behind sleep1: %d\n", sle_ret);

     return 0;
}
