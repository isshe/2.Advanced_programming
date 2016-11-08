/*=========================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p433_pager_program_more.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/11/06
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
#include <sys/wait.h>

#define	DEF_PAGER	"/bin/more"// -d"		/* default pager program */

int
main(int argc, char *argv[])
{
	int		n;
	int		fd[2];
	pid_t	pid;
	char	*pager, *argv0;
	char	line[MAXLINE];
	FILE	*fp;

	if (argc != 2)
		err_quit("usage: a.out <pathname>");

	if ((fp = fopen(argv[1], "r")) == NULL)
		err_sys("can't open %s", argv[1]);
	if (pipe(fd) < 0)
		err_sys("pipe error");

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid > 0) {								/* parent */
		close(fd[0]);		/* close read end */

		/* parent copies argv[1] to pipe */
		while (fgets(line, MAXLINE, fp) != NULL) {
			n = strlen(line);
			if (write(fd[1], line, n) != n)
				err_sys("write error to pipe");
		}
		if (ferror(fp))
			err_sys("fgets error");

		close(fd[1]);	/* close write end of pipe for reader */

		if (waitpid(pid, NULL, 0) < 0)
			err_sys("waitpid error");
		exit(0);
	} else {										/* child */
		close(fd[1]);	/* close write end */
		if (fd[0] != STDIN_FILENO) {
			if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
				err_sys("dup2 error to stdin");
			close(fd[0]);	/* don't need this after dup2 */
			
//			char buf[16] = {0};
//			read(STDIN_FILENO, buf, 16);
//			fprintf(stderr, "read = %s!!!\n", buf);
		}

		/* get arguments for execl() */
//		if ((pager = getenv("PAGER")) == NULL)
			pager = DEF_PAGER;
		if ((argv0 = strrchr(pager, '/')) != NULL)
			argv0++;		/* step past rightmost slash */
		else
			argv0 = pager;	/* no slash in pager */
			
		char *argv1 = "argv1_isshe";
		fprintf(stderr, "argv0 = %s, pager = %s!!!!\n", argv0, pager);
		
		if (execl(pager, argv0, argv1, (char *)0) < 0)
			err_sys("execl error for %s", pager);
	}
	exit(0);
}
