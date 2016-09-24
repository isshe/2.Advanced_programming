/*==============================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p271_read_time_limit.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/01/06
* Description  : 带时间限制的read函数
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/


#include "apue.h"

static void sig_alrm(int);

int
main(void)
{
    int     n = 0;
    char    line[MAXLINE];

    if (signal(SIGALRM, sig_alrm) == SIG_ERR)
    {
         err_sys("signal(SIGALRM) error");
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
     printf("call sig_alrm\n");
}
