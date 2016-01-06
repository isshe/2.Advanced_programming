/*==============================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p272_read_time_limit_longjmp.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/01/06
* Description  : 使用longjmp, 带时间限制调用read()
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/


#include "apue.h"
#include <setjmp.h>

static void sig_alrm(int);
static jmp_buf  env_alrm;

int
main(void)
{
    int     n = 0;
    char    line[MAXLINE];

    if (signal(SIGALRM, sig_alrm) == SIG_ERR)
    {
         err_sys("signal(SIGALRM) error");
    }

    if (setjmp(env_alrm) != 0)
    {
        err_quit("read timeout");
    }

    alarm(5);
    if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
    {
         err_sys("read error");
    }
    alarm(0);

    write(STDOUT_FILENO, line, n);

    exit(0);
}

static void
sig_alrm(int signo)
{
     longjmp(env_alrm, 1);
}
