/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p442_add.c
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

int
main(void)
{
	int		n, int1, int2;
	char	line[MAXLINE];

	while ((n = read(STDIN_FILENO, line, MAXLINE)) > 0) {
		line[n] = 0;		/* null terminate */
		if (sscanf(line, "%d%d", &int1, &int2) == 2) {
			sprintf(line, "%d\n", int1 + int2);
			n = strlen(line);
			if (write(STDOUT_FILENO, line, n) != n)
				err_sys("write error");
		} else {
			if (write(STDOUT_FILENO, "invalid args\n", 13) != 13)
				err_sys("write error");
		}
	}
	exit(0);
}
