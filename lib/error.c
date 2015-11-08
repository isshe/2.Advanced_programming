/*==============================================================================\
* Copyright(C)2015 Chudai.
*
* File name    : error.c
* Version      : v1.0.0
* Author       : 初代
* Date         : 2015/08/31
* Description  : 一些错误显示函数
* Function list: 1.err_ret();
*                2.
*                3.
* History      :
\*==============================================================================*/

#include "apue.h"

static void     err_doit(int, int, const char *, va_list);


/*==============================================================================\
* Function   (名称): err_ret();
* Description(功能): 系统调用, 非致命错误, 打印错误信息, 返回并不终止
* Called By  (被调): 1.
* Calls list (调用): 1.
* Input      (输入): 1.
* Output     (输出): 1.
* Return     (返回): 无返回
*         success  :
*         error    :
* Others     (其他): 1.
\*==============================================================================*/
void err_ret(const char *fmt, ...)
{
     va_list ap;

     va_start(ap, fmt);
     err_doit(1, errno, fmt, ap);
     va_end(ap);

}


/*==============================================================================\
* Function   (名称): err_sys();
* Description(功能): 系统调用, 致命错误, 打印错误信息, 终止
* Called By  (被调): 1.
* Calls list (调用): 1.
* Input      (输入): 1.
* Output     (输出): 1.
* Return     (返回): "1"
*         success  :
*         error    :
* Others     (其他): 1.
\*==============================================================================*/
void
err_sys(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(1, errno, fmt, ap);
	va_end(ap);
	exit(1);
}



/*==============================================================================\
* Function   (名称): err_cont();
* Description(功能):  非系统调用, 非致命错误, 打印错误信息, 返回, 不终止
*                    通过显式参数传递错误代码
* Called By  (被调): 1.
* Calls list (调用): 1.
* Input      (输入): 1.
* Output     (输出): 1.
* Return     (返回):
*         success  :
*         error    :
* Others     (其他): 1.
\*==============================================================================*/
void
err_cont(int error, const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(1, error, fmt, ap);
	va_end(ap);
}


/*==============================================================================\
* Function   (名称): err_exit();
* Description(功能): 非系统调用, 致命错误, 打印信息, 终止
*                   通过显式参数传递错误代码
* Called By  (被调): 1.
* Calls list (调用): 1.
* Input      (输入): 1.
* Output     (输出): 1.
* Return     (返回):
*         success  :
*         error    :
* Others     (其他): 1.
\*==============================================================================*/
void
err_exit(int error, const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(1, error, fmt, ap);
	va_end(ap);
	exit(1);
}


/*==============================================================================\
* Function   (名称): err_dump();
r Description(功能): 系统调用, 致命错误, 打印错误信息, 终止 
* Called By  (被调): 1.
* Calls list (调用): 1.
* Input      (输入): 1.
* Output     (输出): 1.
* Return     (返回):
*         success  :
*         error    :
* Others     (其他): 1.
\*==============================================================================*/
void
err_dump(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(1, errno, fmt, ap);
	va_end(ap);
	abort();		/* dump core and terminate */
	exit(1);		/* shouldn't get here */
}


/*==============================================================================\
* Function   (名称): err_msg();
* Description(功能): 非系统调用, 非致命错误, 打印错误信息, 返回不终止
* Called By  (被调): 1.
* Calls list (调用): 1.
* Input      (输入): 1.
* Output     (输出): 1.
* Return     (返回):
*         success  :
*         error    :
* Others     (其他): 1.
\*==============================================================================*/
void
err_msg(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(0, 0, fmt, ap);
	va_end(ap);
}



/*==============================================================================\
* Function   (名称): err_quit();
* Description(功能): 不是系统调用, 致命错误, 打印错误信息, 终止
* Called By  (被调): 1.
* Calls list (调用): 1.
* Input      (输入): 1.
* Output     (输出): 1.
* Return     (返回):
*         success  :
*         error    :
* Others     (其他): 1.
\*==============================================================================*/
void
err_quit(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(0, 0, fmt, ap);
	va_end(ap);
	exit(1);
}


/*==============================================================================\
* Function   (名称): err_doit();
* Description(功能):
* Called By  (被调): 1.
* Calls list (调用): 1.
* Input      (输入): 1.
* Output     (输出): 1.
* Return     (返回):
*         success  :
*         error    :
* Others     (其他): 1.
\*==============================================================================*/
static void
err_doit(int errnoflag, int error, const char *fmt, va_list ap)
{
    char    buf[MAXLINE] = {0};

    //将参数格式化输出到一个字符数组
    vsnprintf(buf, MAXLINE - 1, fmt, ap);

    if (errnoflag)
    {
         snprintf(buf + strlen(buf), MAXLINE -strlen(buf) - 1,
                 ": %s",  strerror(error));
    }

    strcat(buf, "\n");

    fflush(stdout);         //incase stdout and stderr are the same
    fputs(buf, stderr);
    fflush(NULL);           //flushes all stdio output streams
}
