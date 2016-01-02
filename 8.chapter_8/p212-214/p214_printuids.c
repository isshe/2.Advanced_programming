/*==============================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p214_printuids.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/01/02
* Description  : 打印实际用户ID和有效用户ID
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"

int
main(void)
{
    printf("real uid = %d, effective uid = %d\n",
            getuid(), geteuid());

    exit(0);
}
