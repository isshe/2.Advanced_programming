/*==============================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p270_2_signal_sleep2.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/01/06
* Description  : 在一个捕捉其他信号的程序中调用sleep2()
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/


#include "apue.h"

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


//unsigned int    sleep(unsigned int);
static void     sig_int(int);

int
main (void)
{
    unsigned int unslept;

    if (signal(SIGINT, sig_int) == SIG_ERR)
    {
         err_sys("signal(SIGINT) error");
    }

//    unslept = sleep2(5);
    unslept = sleep(3);
    printf("sleep2 returned: %u\n", unslept);
    exit(0);
}

static void
sig_int(int signo)
{
     int    i = 0 ;
     int    j = 0;
     volatile long k = 0;

     printf("\nsig_int starting\n");
     for (i = 0; i < 300000; i++)
     {
         for (j = 0; j < 20000; j++)
         {
             k += i * j;
         }
     }

     printf("sig_int finished\n");
}
