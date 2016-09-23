/*==============================================================================\
* Copyright(C)2016 Chudai.
*
* File name    : p208_interpreter_file.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2016/01/02
* Description  : 执行一个解释器文件程序, 注意自己建的testinterp文件要chmod+x设置权限。
* Function list: 1.
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"
#include <sys/wait.h>

int
main(void)
{
    pid_t   pid ;

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)
    {
         if (execl("/home/isshe/Nutstore/Code/2.Advanced_programming/8.chapter_8/testinterp",
                     "testintp", "myarg1", "MY ARG2", (char *)0) < 0)
         {
             err_sys("execl error");
         }
    }

    if (waitpid(pid, NULL, 0) < 0)
    {
         err_sys("waitpid error");
    }

    exit(0);
}
