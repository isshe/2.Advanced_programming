/*==============================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p197_race_condition.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/01/01
* Description  : 使用TELL/WAIT函数避免竞争条件， 但是这两个函数目前还没有实现！
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

     TELL_WAIT();               //+++

     if ((pid = fork()) < 0)
     {
          err_sys("fork error");
     }
     else if (pid == 0)
     {
         WAIT_PARENT();         //++++
          charatatime("output form child\n");
     }
     else
     {
          charatatime("output from parent\n");
          TELL_CHILD(pid);      //+++:
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
