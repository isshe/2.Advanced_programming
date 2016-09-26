/*==============================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : my_system.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/01/02
* Description  : system函数的一种实现， 没有对信号进行处理
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

int
system(const char *cmdstring)    //version without signal handling
{
    pid_t   pid;
    int     status = 0;

    if (cmdstring == NULL)
    {
         return (1);
    }

    if ((pid = fork()) < 0)
    {
        status = -1;            //probably out of processes
    }
    else if (pid == 0)          //child
    {
         execl("/bin/sh","xxxxxxxxxxxx11111", "-c", cmdstring, (char *)0);
         _exit(127);
    }
    else                        //parent
    {
        while (waitpid(pid, &status, 0) < 0)
        {
             if (errno != EINTR)
             {
                 status = -1;       //error other than EINTR form waitpid
                 break;
             }
        }
    }

    return (status);
}
