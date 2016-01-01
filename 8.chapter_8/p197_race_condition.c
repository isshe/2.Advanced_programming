/*==============================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p197_race_condition.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/01/01
* Description  : 带有竞争条件的程序
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/


#include "apue.h"

static  void    charatatime(char *);

int
main(void)
{
     pid_t  pid;

     if ((pid = fork()) < 0)
     {
          err_sys("fork error");
     }
     else if (pid == 0)
     {
          charatatime("output form child\n");
     }
     else
     {
          charatatime("output from parent\n");
     }

     exit(0);
}

static void
charatatime(char *str)
{
     char   *ptr;
     int    c ;

     setbuf(stdout, NULL);  //set unbuffered
     for (ptr = str; (c = *ptr++) != 0; )
     {
          putc(c, stdout);
     }
}
