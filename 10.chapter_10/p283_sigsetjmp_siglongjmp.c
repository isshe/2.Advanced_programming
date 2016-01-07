/*==============================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p283_sigsetjmp_siglongjmp.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/01/07
* Description  : 信号屏蔽,sigsetjmp(), siglongjmp的实例,
*                   使用到p275页的pr_mask().
*                我们期望:当调用一个信号处理函数时,
*                被捕捉到的信号加到进程的当前信号屏蔽字中,
*                当从信号处理函数返回时, 恢复原来的屏蔽字.
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

//pr_mask的功能: 打印被屏蔽的信号的符号表示.

#include "apue.h"
#include <setjmp.h>
#include <time.h>

void pr_mask(const char *str);

static void         sig_usr1(int);
static void         sig_alrm(int);
static sigjmp_buf  jmpbuf;         //sig***jmp()使用
//sig_atomic_t是由ISO C 标准定义的变量类型,
//在写这种变量的时候不会被中断!
static volatile sig_atomic_t    canjmp;

int
main (void)
{
     if (signal(SIGUSR1, sig_usr1) == SIG_ERR)
     {
         err_sys("signal(SIGUSR1) error");
     }

     if (signal(SIGALRM, sig_alrm) == SIG_ERR)
     {
          err_sys("signal(SIGALRM) error");
     }

     pr_mask("starting main: ");        //p275

     if (sigsetjmp(jmpbuf, 1))          //!0进入
     {
          pr_mask("ending main: ");

          exit(0);
     }
     canjmp = 1;        //when if(==0).

     while(1)
     {
          pause();      //
     }

}

static void
sig_usr1(int signo)
{
     time_t     starttime;

     if (canjmp == 0)
     {
         return ;       //unexpected signal, ignore
     }

     pr_mask("staring sig_usr1: ");

     alarm(3);      //send SIGALRM when time out.
     starttime = time(NULL);    //获取系统时间, 但是作用是什么呢?
     while(1)
     {
          if (time(NULL) > starttime + 5)    //busy wait for 5 second
          {
              break;
          }
     }

     pr_mask("finishing sig_usr1: ");

     canjmp = 0;
     siglongjmp(jmpbuf, 1);     // jmp back to main


}

static void
sig_alrm(int signo)
{
     pr_mask("in sig_alrm: ");
}
