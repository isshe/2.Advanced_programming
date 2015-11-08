/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : str_perror_p12.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/11/08
* Description  :
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"
#include <errno.h>

int main(int argc, char *argv[])
{
    fprintf(stderr, "EACCES: %s\n", strerror(EACCES));

    errno = ENOENT;
    perror(argv[0]);

    exit(0);
}
