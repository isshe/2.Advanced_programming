/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p187_vfork.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/09/23
* Description  :
* Function list: 1.
*                2.
*                3.
* History      :
\*=========================================================================*/

/*-----------------------------------------------------------*
 * 头文件                                                    *
 *-----------------------------------------------------------*/
#include <unistd.h>
#include "apue.h"

int globvar = 6;

int main(void)
{
     int    var = 0;
     pid_t  pid ;
     int    printfstatus = 0;

     var = 88;
     printf("before bfork\n");  //不冲洗缓冲区

     if ((pid = vfork()) < 0)
     {
          err_sys("vork error");
     }
     else if (pid == 0)
     {
         globvar++;
         var++;
         fclose(stdout);
         exit(0);
     }

//     fclose(stdout);
     printfstatus = printf("pid = %ld, glob = %d, var = %d\n",
             (long)getpid(), globvar, var);

     fprintf(stderr, "pstatus = %d\n", printfstatus);
     exit(printfstatus);
//    exit(111);
}
