/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : p54_lseek.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/11/09
* Description  :
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"

int main(void )
{
     if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
     {
         printf("cannot seek\n");
     }
     else
     {
          printf("seek ok\n");
     }


     exit(0);
}
