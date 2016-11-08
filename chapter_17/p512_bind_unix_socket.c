/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p512_bind_unix_socket.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/11/09
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
#include <sys/socket.h>
#include <sys/un.h>

int
main(void)
{
	int fd, size;
	struct sockaddr_un un;

	un.sun_family = AF_UNIX;
	strcpy(un.sun_path, "foo.socket");
	if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
		err_sys("socket failed");
	size = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);
	if (bind(fd, (struct sockaddr *)&un, size) < 0)
		err_sys("bind failed");
	printf("UNIX domain socket bound\n");
	exit(0);
}
