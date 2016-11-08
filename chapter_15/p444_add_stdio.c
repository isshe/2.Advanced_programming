/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p444_add_stdio.c
* Version      : v1.0.0ls
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
	int		int1, int2;
	char	line[MAXLINE];

	//下面四行改进
	if (setvbuf(stdin, NULL, _IOLBF, 0) != 0)
		err_sys("setvbuf error");
	if (setvbuf(stdout, NULL, _IOLBF, 0) != 0)
		err_sys("setvbuf error");
		
	while (fgets(line, MAXLINE, stdin) != NULL) {
		if (sscanf(line, "%d%d", &int1, &int2) == 2) {
			if (fprintf(stdout, "%d\n", int1 + int2) == EOF)
				err_sys("printf error");
		} else {
			if (printf("invalid args\n") == EOF)
				err_sys("printf error");
		}
	}
	exit(0);
}
