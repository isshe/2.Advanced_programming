/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p440_to_lower.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/11/07
* Description  :
* Function list: 1.
*                2.
*                3.
* History      :
\*=========================================================================*/

/*-----------------------------------------------------------*
 * 头文件                                                    *
 *-----------------------------------------------------------*/
#include "apue.h"
#include <ctype.h>

int
main(void)
{
	int		c;

	while ((c = getchar()) != EOF) {
		if (isupper(c))
			c = tolower(c);
		if (putchar(c) == EOF)
			err_sys("output error");
		if (c == '\n')
			fflush(stdout);
	}
	exit(0);
}
