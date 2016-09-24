/*==============================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p270_sleep2_setjmp.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/01/06
* Description  : 使用setjmp()和longjmp()的sleep实现, 同样是不完善的实现
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>      //main

static jmp_buf  env_alrm;

static void
sig_alrm(int signo)
{
    longjmp(env_alrm, 1);
}

unsigned int
sleep2(unsigned int seconds)
{
     if (signal(SIGALRM, sig_alrm) == SIG_ERR)
     {
         return(seconds);
     }

     if (setjmp(env_alrm) == 0)
     {
          alarm(seconds);
          while(1);             //这样也可以的样子哦???
 //         pause();
     }

     return (alarm(0));
}

int
main(void)
{
     sleep2(2);

     return 0;
}
